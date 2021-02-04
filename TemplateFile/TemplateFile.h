/* 
Copyright 2019-2020 hkm(github:hihkm)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */

/* 
Copyright 2019-2020 hkm(github:hihkm)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 */

#ifndef __TEMPLATE_FILE_H__
#define __TEMPLATE_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Define/DanmakuDef.h"
#include "../Define/Status.h"
#include "../String/DanmakuFactoryString.h"

#define LINE_MAX_LEN 4096
#define FORMAT_TABLE_MAX_LEN 256
#define STR_TABLE_MAX_LEN 128
#define READ_BUFFER_SIZE LINE_MAX_LEN * 5

#define TAR_NULL 0
#define TAR_FORMAT 1
#define TAR_SET_TIME 2
#define TAR_SET_TYPE 3
#define TAR_SET_COLOR 4
#define TAR_SET_FONTSIZE 5

#define FORMAT_TIME -1
#define FORMAT_TYPE -2
#define FORMAT_COLOR -3
#define FORMAT_FONTSIZE -4
#define FORMAT_TEXT -5
#define FORMAT_ANYNUM -6
#define FORMAT_ANYSTR -7

#define HAVE_NOT_BEEN_SET -1

#define FORMAT_IS_VAR(tableValue) (tableValue < 0)

struct formatOfDanmaku
{
    char *strTable[STR_TABLE_MAX_LEN];    /* 字串表 */
    int formatTable[FORMAT_TABLE_MAX_LEN];/* 格式表 */
    int strTableLen;
    int formatTableLen;
    /* 
     * 格式表表示方法： 按顺序用整形存储每一个部分，宏定义 FORMAT_XXX 表示读取某类型值，正整数表示字串表下标，对于某一字符串
     */
};

struct timeDefineSetting
{
    float ratioToSeconds;
};

struct typeDefineSetting
{
    int rightToLeft;
    int leftToRight;
    int topFix;
    int bottomFix;
    int defaultType;
};

struct colorDefineSetting
{
    int defaultColor;
};

struct fontsizeDefineSetting
{
    int defaultFontsize;
};

typedef struct formatOfDanmaku FORMAT;
typedef struct timeDefineSetting SET_TIME;
typedef struct typeDefineSetting SET_TYPE;
typedef struct colorDefineSetting SET_COLOR;
typedef struct fontsizeDefineSetting SET_FONTSIZE;

extern int readTemplateFile(const char *const ipFile, const char *const templateFile, 
                     DANMAKU **danmakuHead, const char *mode, const float timeShift, 
                     STATUS *const status, char *errMsg, int msgLen);

#ifdef __cplusplus
}
#endif

#endif
