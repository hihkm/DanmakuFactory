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
#include <stdlib.h>
#include <string.h>
#include "../String/DanmakuFactoryString.h"
#include "../Define/DanmakuDef.h"

#define SIZE_OF_BUF 4096
#define KEY_LEN 128
#define VALUE_LEN 512
#define TYPENAME_LEN 64

struct Configurations
{
    int resx;          /*分辨率宽*/
    int resy;          /*分辨率高*/
    float scrolltime;  /*滚动时间*/
    float fixtime;     /*固定时间*/
    int density;       /*密度*/
    int fontsize;      /*字号*/
    char fontname[FONTNAME_LEN]; /*字体*/
    int opacity;       /*不透明度*/
    int outline;       /*描边*/
    int shadow;        /*阴影*/
    float displayarea; /*显示区域*/
    float scrollarea;  /*滚动区域*/
    BOOL saveBlockedPart;  /*是否保存屏蔽部分*/
    int blockmode;     /*屏蔽模式*/
    int statmode;      /*统计模式*/
};

typedef struct Configurations CONFIG;

extern CONFIG readConfig(const char *const configFileName, const CONFIG defaultConfig);
extern BOOL writeConfig(const char *const configFileName, const CONFIG newConfig);

#ifdef __cplusplus
}
#endif

#endif
