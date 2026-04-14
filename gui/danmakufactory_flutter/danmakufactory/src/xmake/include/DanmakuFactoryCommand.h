#ifndef DANMAKUFACTORYCOMMAND_H
#define DANMAKUFACTORYCOMMAND_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

/* 错误码定义 */
#define EXIT_SUCCESS_CODE 0      /* 成功 */
#define EXIT_ERR_ARGS 1          /* 参数错误 */
#define EXIT_ERR_FILE 2          /* 文件操作错误 */
#define EXIT_ERR_MEMORY 3        /* 内存错误 */
#define EXIT_ERR_FORMAT 4        /* 格式错误 */
#define EXIT_ERR_CONFIG 5        /* 配置错误 */
#define EXIT_ERR_INTERNAL 6      /* 内部错误 */

#ifdef __cplusplus
extern "C"
{
#endif

EXPORT int runCommand(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif