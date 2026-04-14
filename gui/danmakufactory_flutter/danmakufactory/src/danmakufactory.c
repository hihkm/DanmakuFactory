#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "danmakufactory.h"
#include "xmake/include/hi.h"
#include "xmake/include/DanmakuFactoryCommand.h"
#include "log/logger.h"

FFI_PLUGIN_EXPORT int sum(int a, int b) { return a + b; }

FFI_PLUGIN_EXPORT int sum_long_running(int a, int b) {
#if _WIN32
  Sleep(5000);
#else
  usleep(5000 * 1000);
#endif
  return a + b;
}

FFI_PLUGIN_EXPORT const char* testHi(){
  return hi();
}


// 辅助函数：解析命令行字符串为 argc/argv 格式
// 支持双引号和单引号包裹的带空格路径
static int parse_command_line(char *cmd, char **argv, int max_args) {
    int argc = 0;
    char *p = cmd;
    int in_quote = 0;
    char quote_char = 0;

    // 添加程序名作为第一个参数 (argv[0])
    argv[argc++] = "DanmakuFactory";

    while (*p && argc < max_args) {
        // 跳过开头的空格
        while (*p && isspace((unsigned char)*p)) p++;
        if (*p == '\0') break;

        if (*p == '"' || *p == '\'') {
            in_quote = 1;
            quote_char = *p++;
            argv[argc++] = p;
            while (*p && *p != quote_char) p++;

            if (*p == quote_char) {
                *p = '\0';
                p++;
            }
        } else {
            argv[argc++] = p;
            while (*p && !isspace((unsigned char)*p)) p++;
        }

        if (*p) {
            *p = '\0'; // 截断字符串
            p++;
        }
    }
    return argc;
}

FFI_PLUGIN_EXPORT int runCmd(const char* cmd) {
    if (cmd == NULL) return -1;

    size_t len = strlen(cmd) + 1;

    char *cmd_copy = (char*)malloc(len);
    if (!cmd_copy) return -1;

    memcpy(cmd_copy, cmd, len);

    const int MAX_ARGS = 128;
    char **argv = (char**)malloc(sizeof(char*) * (MAX_ARGS + 1));
    if (!argv) {
        free(cmd_copy);
        return -1;
    }

    int argc = parse_command_line(cmd_copy, argv, MAX_ARGS);

    if (argc <= 0) {
        free(cmd_copy);
        free(argv);
        return -1;
    }

    LOGD("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        LOGD("argv[%d] = '%s'\n", i, argv[i]);
    }

    int result = runCommand(argc, argv);

    free(cmd_copy);
    free(argv);

    return result;
}

