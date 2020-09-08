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

#ifndef __DANMAKUFACTORY_STRING_H__
#define __DANMAKUFACTORY_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "../Define/DanmakuDef.h"

#define CHAR_IS_BLANK(ch) (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
#define STR_IS_EMPTY(str) (str[0] == '\0')
#define STR_IS_BLANK(str) (isDesignatedStr(str, " \n\t\r"))
#define TO_STR_END(ptr)   (ptr += strlen(ptr))

/*移动字符指针向后跳到距离为字符串prefix的长度的位置*/
#define STR_PTR_JUMP(strPtr, prefix)         \
{                                            \
    strPtr += strlen(prefix) * sizeof(char); \
}

extern int getStrHei(const unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName);
extern int getStrLen(const unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName);
extern char *floatToStr(char *const outputStr, const double input, const int accuracy);
extern char *strGetLeftPart(char *const opStr, char **const ipStr, const char cutCh, const int maxLen);
extern char *trim(char *const str);
extern char *deQuotMarks(char *const str);
extern char *toLower(char *output, char *input);
extern int lastChr(const char *const str, const char chr);
extern BOOL isDesignatedChar(char ch, const char *designatedChar);
extern BOOL isDesignatedStr(char *str, char *designatedChar);
extern BOOL isUtf8(char const *const str);
extern char *strSafeCopy(char *destination, const char *const source, size_t count);
extern int match(char *mainStr, char *patternStr);
extern char *strrpl(char *inStr, char *outStr, char *srcStr, char *dstStr, int outBuffSize);
extern BOOL isStartWith(const char *const mainStr, const char *const prefixStr);
extern char *getNextWord(char **ptr, char *buf, int maxLen, char endBefore, BOOL isMovePtr);

#ifdef __cplusplus
}
#endif

#endif