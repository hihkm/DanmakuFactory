#ifndef NATIVE_LOGGER_H
#define NATIVE_LOGGER_H

#include <stdio.h>

#ifdef __ANDROID__
#include <android/log.h>
#define TAG "FFI_NATIVE"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#elif defined(__OHOS__)
#include <hilog/log.h>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0xFF00
#define LOG_TAG "FFI_NATIVE"

// 宏：先格式化字符串，再传给 OH_LOG_Print
#define LOGD(fmt, ...) do { \
    char _buf[512]; \
    snprintf(_buf, sizeof(_buf), fmt, ##__VA_ARGS__); \
    OH_LOG_Print(LOG_APP, LOG_DEBUG, LOG_DOMAIN, LOG_TAG, "%{public}s", _buf); \
} while(0)

#define LOGI(fmt, ...) do { \
    char _buf[512]; \
    snprintf(_buf, sizeof(_buf), fmt, ##__VA_ARGS__); \
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_DOMAIN, LOG_TAG, "%{public}s", _buf); \
} while(0)

#define LOGE(fmt, ...) do { \
    char _buf[512]; \
    snprintf(_buf, sizeof(_buf), fmt, ##__VA_ARGS__); \
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_DOMAIN, LOG_TAG, "%{public}s", _buf); \
} while(0)

#elif defined(__APPLE__)
#include <syslog.h>
#define LOGD(...) { printf("DEBUG: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define LOGI(...) { printf("INFO: ");  printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define LOGE(...) { printf("ERROR: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

#else
#define LOGD(...) { printf("DEBUG: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define LOGI(...) { printf("INFO: ");  printf(__VA_ARGS__); printf("\n"); fflush(stdout); }
#define LOGE(...) { printf("ERROR: "); printf(__VA_ARGS__); printf("\n"); fflush(stdout); }

#endif

#endif