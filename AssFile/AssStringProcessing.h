/* 
Copyright 2019-2021 hkm(github:hihkm)

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

#ifndef __ASS_STRING_PROCESSING_H__
#define __ASS_STRING_PROCESSING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../CDanmakuFactory.h"

//TODO: sc框文本宽度补偿值 有准确测长方法请移除
#define SCBOX_TXT_LEN_COMPENSATION 0.9

#define ASS_ESCAPE 0
#define ASS_UNESCAPE 1

struct AssEscapeListNode
{
    char *originalText;
    char *assEscapedText;
};

extern char *toHexOpacity(int decOpacity, char *hexOpacity);
extern char *toHexColor(int decColor, char *hexColor);
extern int toDecColor(char *hexColor);
extern char *deStyleNamePrefix(char *str);
extern float timeToFloat(const char *ipStr);
extern void arrset(int *array, const int value, const int numberOfMember);
char *assEscape(char *dstStr, char *srcStr, int dstStrLen, int mode);

#ifdef __cplusplus
}
#endif

#endif