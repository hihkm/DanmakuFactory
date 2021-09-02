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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../String/DanmakuFactoryString.h"
#include "../Define/DanmakuDef.h"

#define SIZE_OF_BUF 4096
#define KEY_LEN 128
#define VALUE_LEN 512
#define TYPENAME_LEN 64

struct Coordinate
{
    int x;
    int y;
};

struct Configurations
{
    struct Coordinate resolution; /* 分辨率 */
    float displayarea; /* 显示区域 */
    float scrollarea;  /* 滚动区域 */
    float scrolltime;  /* 滚动时间 */
    float fixtime;     /* 固定时间 */

    int density;       /* 密度 */
    int fontsize;      /* 字号 */
    char fontname[FONTNAME_LEN]; /* 字体 */
    int opacity;       /* 不透明度 */
    int outline;       /* 描边 */
    int shadow;        /* 阴影 */
    BOOL bold;         /* 是否加粗 */

    BOOL saveBlockedPart;  /* 是否保存屏蔽部分 */
    BOOL showUserNames;    /* 是否显示用户名 */
    BOOL showMsgBox;       /* 是否显示消息框 */

    struct Coordinate msgBoxSize; /* 消息框大小 */
    struct Coordinate msgBoxPos;  /* 消息框位置 */
    int msgboxFontsize;           /* 消息框内文字大小 */
    float giftMinPrice;           /* 消息框礼物最低价格限制 */

    int blockmode;     /* 屏蔽模式 */
    int statmode;      /* 统计模式 */
};

typedef struct Coordinate COORDIN;
typedef struct Configurations CONFIG;

extern CONFIG readConfig(const char *const configFileName, const CONFIG defaultConfig);
extern BOOL writeConfig(const char *const configFileName, const CONFIG newConfig);
extern void printConfig(CONFIG config);

#ifdef __cplusplus
}
#endif

#endif
