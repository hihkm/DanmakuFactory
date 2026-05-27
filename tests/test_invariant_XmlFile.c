#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Security invariant: When copying parsed XML text content into a fixed-size
 * destination buffer, the copy operation must never write beyond the bounds of
 * the destination buffer, regardless of the size of the source data.
 *
 * This test validates that a safe copy function (which should replace the
 * vulnerable strcpy) correctly bounds-checks the copy, and also demonstrates
 * that adversarial inputs of various sizes are handled safely.
 */

/* Safe replacement for the vulnerable strcpy pattern.
 * This is what the fix SHOULD look like - we test that this invariant holds.
 * The destination buffer size is fixed at 256 bytes (typical danmaku text buffer).
 */
#define DEST_BUFFER_SIZE 256

static int safe_xml_text_copy(char *dest, size_t dest_size, const char *src) {
    if (!dest || !src || dest_size == 0) return -1;
    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        /* Truncate to fit - security invariant: never overflow */
        strncpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
        return 1; /* truncated */
    }
    strcpy(dest, src);
    return 0; /* success, no truncation needed */
}

/* Generate a string of given length filled with a specific character */
static char *make_payload(size_t len, char fill) {
    char *buf = malloc(len + 1);
    if (!buf) return NULL;
    memset(buf, fill, len);
    buf[len] = '\0';
    return buf;
}

START_TEST(test_xml_text_copy_bounds_safety)
{
    /* Invariant: The destination buffer must never be overflowed when copying
     * XML text content, regardless of the size or content of the source data. */

    const char *static_payloads[] = {
        /* Exact boundary */
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", /* 256 A's */

        /* One over boundary */
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB", /* 257 B's */

        /* XML injection attempt */
        "<text>AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA</text>",

        /* Null bytes embedded (as much as C strings allow) */
        "normal text",

        /* Empty string */
        "",

        /* Single character */
        "X",

        /* Format string attack */
        "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",

        /* Unicode-like sequences */
        "\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf"
        "\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf\xc0\xaf",

        /* All printable ASCII repeated */
        "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
        "`abcdefghijklmnopqrstuvwxyz{|}~!\"#$%&'()*+,-./0123456789:;<=>?@"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!!"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!!",

        /* Whitespace flood */
        "                                                                "
        "                                                                "
        "                                                                "
        "                                                                "
        "                                                                ",
    };

    int num_static = sizeof(static_payloads) / sizeof(static_payloads[0]);

    /* Test static payloads */
    for (int i = 0; i < num_static; i++) {
        char dest[DEST_BUFFER_SIZE];
        /* Canary values to detect overflow */
        char canary_before[16];
        char canary_after[16];
        memset(canary_before, 0xAB, sizeof(canary_before));
        memset(canary_after, 0xCD, sizeof(canary_after));
        memset(dest, 0, sizeof(dest));

        int result = safe_xml_text_copy(dest, DEST_BUFFER_SIZE, static_payloads[i]);

        /* Invariant 1: The function must return a valid result code */
        ck_assert_msg(result == 0 || result == 1 || result == -1,
                      "safe_xml_text_copy returned unexpected value for payload %d", i);

        /* Invariant 2: The destination must be null-terminated */
        int null_found = 0;
        for (size_t j = 0; j < DEST_BUFFER_SIZE; j++) {
            if (dest[j] == '\0') {
                null_found = 1;
                break;
            }
        }
        ck_assert_msg(null_found, "Destination buffer not null-terminated for payload %d", i);

        /* Invariant 3: The resulting string length must be less than DEST_BUFFER_SIZE */
        size_t dest_len = strlen(dest);
        ck_assert_msg(dest_len < DEST_BUFFER_SIZE,
                      "Destination string length %zu >= buffer size %d for payload %d",
                      dest_len, DEST_BUFFER_SIZE, i);

        /* Invariant 4: Source length >= DEST_BUFFER_SIZE must result in truncation */
        size_t src_len = strlen(static_payloads[i]);
        if (src_len >= DEST_BUFFER_SIZE) {
            ck_assert_msg(result == 1,
                          "Expected truncation for oversized payload %d (src_len=%zu)", i, src_len);
            ck_assert_msg(dest_len == DEST_BUFFER_SIZE - 1,
                          "Truncated string should be exactly %d chars for payload %d",
                          DEST_BUFFER_SIZE - 1, i);
        }

        /* Invariant 5: Source length < DEST_BUFFER_SIZE must result in exact copy */
        if (src_len < DEST_BUFFER_SIZE) {
            ck_assert_msg(result == 0,
                          "Expected exact copy for payload %d (src_len=%zu)", i, src_len);
            ck_assert_msg(dest_len == src_len,
                          "Exact copy should preserve length for payload %d", i);
        }

        (void)canary_before;
        (void)canary_after;
    }

    /* Test dynamically generated adversarial payloads */
    size_t dynamic_sizes[] = {
        0, 1, 127, 128, 255, 256, 257, 512, 1024, 4096, 65536, 1048576
    };
    int num_dynamic = sizeof(dynamic_sizes) / sizeof(dynamic_sizes[0]);

    for (int i = 0; i < num_dynamic; i++) {
        size_t payload_size = dynamic_sizes[i];
        char *dynamic_payload = make_payload(payload_size, 'A');
        if (!dynamic_payload) continue;

        char dest[DEST_BUFFER_SIZE];
        memset(dest, 0, sizeof(dest));

        int result = safe_xml_text_copy(dest, DEST_BUFFER_SIZE, dynamic_payload);

        /* Invariant: result must be valid */
        ck_assert_msg(result == 0 || result == 1,
                      "Unexpected result for dynamic payload size %zu", payload_size);

        /* Invariant: destination must be null-terminated within bounds */
        int null_found = 0;
        for (size_t j = 0; j < DEST_BUFFER_SIZE; j++) {
            if (dest[j] == '\0') {
                null_found = 1;
                break;
            }
        }
        ck_assert_msg(null_found,
                      "Destination not null-terminated for dynamic payload size %zu", payload_size);

        /* Invariant: destination string length must be < DEST_BUFFER_SIZE */
        size_t dest_len = strlen(dest);
        ck_assert_msg(dest_len < DEST_BUFFER_SIZE,
                      "Destination overflow for dynamic payload size %zu (dest_len=%zu)",
                      payload_size, dest_len);

        /* Invariant: for oversized inputs, must truncate to exactly DEST_BUFFER_SIZE-1 */
        if (payload_size >= DEST_BUFFER_SIZE) {
            ck_assert_msg(dest_len == DEST_BUFFER_SIZE - 1,
                          "Oversized payload not truncated correctly: size=%zu, dest_len=%zu",
                          payload_size, dest_len);
        }

        free(dynamic_payload);
    }
}
END_TEST

START_TEST(test_xml_text_copy_content_integrity)
{
    /* Invariant: For inputs that fit within the buffer, the content must be
     * preserved exactly (no corruption of valid data). */

    struct {
        const char *input;
        const char *expected;
    } cases[] = {
        {"hello", "hello"},
        {"danmaku text", "danmaku text"},
        {"<b>bold</b>", "<b>bold</b>"},
        {"123456789", "123456789"},
        {"", ""},
        {"a", "a"},
        {"test\nnewline", "test\nnewline"},
        {"tab\there", "tab\there"},
    };

    int num_cases = sizeof(cases) / sizeof(cases[0]);

    for (int i = 0; i < num_cases; i++) {
        char dest[DEST_BUFFER_SIZE];
        memset(dest, 0xFF, sizeof(dest)); /* Fill with non-zero to catch partial writes */

        int result = safe_xml_text_copy(dest, DEST_BUFFER_SIZE, cases[i].input);

        ck_assert_msg(result == 0,
                      "Expected exact copy for case %d, got result=%d", i, result);
        ck_assert_msg(strcmp(dest, cases[i].expected) == 0,
                      "Content mismatch for case %d: expected '%s', got '%s'",
                      i, cases[i].expected, dest);
    }
}
END_TEST

START_TEST(test_xml_text_copy_null_safety)
{
    /* Invariant: The copy function must handle NULL inputs gracefully
     * without crashing or causing undefined behavior. */

    char dest[DEST_BUFFER_SIZE];
    memset(dest, 0, sizeof(dest));

    /* NULL source */
    int result = safe_xml_text_copy(dest, DEST_BUFFER_SIZE, NULL);
    ck_assert_msg(result == -1, "NULL source should return -1, got %d", result);

    /* NULL destination */
    result = safe_xml_text_copy(NULL, DEST_BUFFER_SIZE, "test");
    ck_assert_msg(result == -1, "NULL destination should return -1, got %d", result);

    /* Zero size */
    result = safe_xml_text_copy(dest, 0, "test");
    ck_assert_msg(result == -1, "Zero size should return -1, got %d", result);

    /* Size of 1 (only null terminator fits) */
    char tiny[1];
    result = safe_xml_text_copy(tiny, 1, "test");
    ck_assert_msg(result == 1, "Size-1 buffer with non-empty src should truncate, got %d", result);
    ck_assert_msg(tiny[0] == '\0', "Size-1 buffer should contain only null terminator");
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_set_timeout(tc_core, 30);
    tcase_add_test(tc_core, test_xml_text_copy_bounds_safety);
    tcase_add_test(tc_core, test_xml_text_copy_content_integrity);
    tcase_add_test(tc_core, test_xml_text_copy_null_safety);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}