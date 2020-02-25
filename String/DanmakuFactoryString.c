/*
Copyright 2019 TIKM(github:HITIKM)

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

#include "DanmakuFactoryString.h"

/*
 * 计算字符串高度
 * 参数： 
 * 字符串指针/字号/字体
 * 返回值：
 * 高度（像素）
 */
int getStrHei(const unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
{
    return fontSizeSet + (fontSizeInFile - 25);
}

/*
 * 计算字符串宽度
 * 参数：
 * 字符串指针/字号/字体
 * 返回值：
 * 宽度（像素） 
 */
int getStrLen(const unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
{
    
    int cnt = 0; 
    
    /*判断字符串编码*/
    if (isUtf8(str) == TRUE)
    {
        /*
         * 目前仅支持utf-8 
         * 首字节          空间占用           起始 
         * 0--- ----        1 byte            0x00 
         * 110- ----        2 byte            0xC0 
         * 1110 ----        3 byte            0xE0
         * 1111 0---        4 byte            0xF0
         * 1111 10--        5 byte            0xF8 
         * 1111 110-        6 byte            0xFC
         */
        while (*str != '\0')
        {
            if (*str >= 0xC0)
            {
                cnt += 2;
            }
            else if (*str < 0x80)
            {
                cnt += 1;
            }
            str++;
        }       
    }
    else
    {
        cnt = strlen(str);
    }
    
    return (fontSizeSet + (fontSizeInFile - 25)) / 2 * cnt;
}

/*
 * 以指定精度的最小数位将浮点数转换为字符串 
 * 参数：输出字符数组/输入浮点数/精度 
 */ 
char *floatToStr(char *const outputStr, const double input, const int accuracy)
{
    int cnt;
    char tempStr[32];
    char *tempPtr;
    sprintf(tempStr, "%lf", input);
    tempPtr = strchr(tempStr, '.');
    
    /*整数*/
    if (tempPtr == NULL)
    {
        strcpy(outputStr, tempPtr);
        return outputStr;
    }
    
    /*小数*/ 
    for (cnt = 0; cnt <= accuracy; cnt++)
    {
        if (*tempPtr == '\0')
        {
            break;
        }
        tempPtr++;
    }
    
    /*寻找末尾第一位非0位*/ 
    while (*(tempPtr-1) == '0')
    {
        tempPtr--;
    }
    
    /*去除小数点*/ 
    if (*(tempPtr-1) == '.')
    {
        tempPtr--;
    }
    *tempPtr = '\0';
    
    strcpy(outputStr, tempStr);
    return outputStr;
}

/*
 * 得到字符串左边部分，并移动指针至截断位置后一个字符
 * 参数：输出字符串/输入字符串指针地址/截断位置/ 
 * 返回值：结果字符串地址 
 * 输出字符串为NULL时 将单纯移动指针 
 */
char *strGetLeftPart(char *const opStr, char **const ipStr, const char cutCh, const int maxLen)
{
    int copiedLen = 0;
    char *leftPtr, *rightPtr;
    char *opPtr = (char *)opStr;
    leftPtr = rightPtr = (char *)*ipStr;
    
    /*移动指针到指定字符位置*/
    while (*rightPtr != '\0' && *rightPtr != cutCh && copiedLen < maxLen)
    {
        rightPtr++;
    }
    
    /*字符串中无指定字符*/ 
    if (*rightPtr == '\0')
    {
        leftPtr = rightPtr;
    }
    
    /*执行拷贝*/ 
    if (opStr != NULL)
    {
        while (leftPtr < rightPtr)
        {
            *opPtr = *leftPtr;
            opPtr++;
            leftPtr++;
        }
        
        *opPtr = '\0';
    }
    
    /*移动指针到下一个位置*/ 
    if (*rightPtr != '\0')
    {
        rightPtr++;
    }
    *ipStr = rightPtr;
    
    return opStr;
}

/*
 * 除去字符串左右空白字符 
 * 参数：
 * 要去除空白字符的字符串/
 * 返回值：
 * 结果字符串/ 
 */
char *trim(char *const str)
{
    /*非法检查*/
    if (str == NULL)
    {
        return NULL;
    }
    
    char *leftPtr, *rightPtr, *reWritePtr;
    leftPtr = str;
    /*寻找左边的第一个非空字符*/
    while (*leftPtr == ' ' || *leftPtr == '\n' || *leftPtr == '\t' || *leftPtr == '\r')
    {
        if (*leftPtr == '\0')
        {
            break;
        }
        leftPtr++;
    }
    
    /*寻找右边的最后一个非空字符*/
    rightPtr = leftPtr;
    while (*rightPtr != '\0')
    {
        rightPtr++;
    }
    
    while (*rightPtr == ' ' || *rightPtr == '\n' || *rightPtr == '\t' || *rightPtr == '\r' || *rightPtr == '\0')
    {
        if (rightPtr == leftPtr)
        {
            break;
        }
        rightPtr--;
    }
    
    /*拷贝左右指针之间的内容*/
    reWritePtr = (char *)str; 
    
    while (leftPtr <= rightPtr)
    {
        *reWritePtr = *leftPtr;
        reWritePtr++;
        leftPtr++;
    } 
    
    *reWritePtr = '\0';
    
    return str; 
}

/*
 * 去字符串一重左右引号(单双引号)，没有的话则不处理
 * 返回值：输入的指针 
 */
char *deQuotMarks(char *const str)
{
    char *strPtr = (char *)str; 
    
    /*非法检查*/
    if (str == NULL)
    {
        return NULL;
    }
    
    trim(str);/*去空白字符*/
    /*去前引号*/
    if (*strPtr == '\"' || *strPtr == '\'')
    {
        while(*(strPtr+1) != '\0')
        {
            *strPtr = *(strPtr + 1);
            strPtr++;
        }
    }
    else
    {
        while (*strPtr != '\0')
        {
            strPtr++;
        }
    }
    
    /*去后引号*/
    if (strPtr != (char *)str && (*(strPtr-1) == '\"' || *(strPtr-1) == '\''))
    {
        strPtr--;
    }
    *strPtr = '\0';
    
    return str;
}

/*
 * 转换成小写字母
 * 参数：
 * 输出字符串地址/输入字符串地址/ 
 * 返回值：
 * 结果字符串地址
 * 若输出字符串地址为NULL，则将直接修改输入字符串
 */
char *toLower(char *output, char *input)
{
    char *ptr;
    if (output == NULL)
    {
        ptr = input;
    }
    else
    {
        strcpy(output, input);
        ptr = output;
    }
    
    while (*ptr != '\0')
    {
        if (*ptr >= 'A' && *ptr <= 'Z')
        {
            *ptr += 'a' - 'A';
        }
        ptr++;
    }
    
    if (output == NULL)
    {
        return input;
    }
    return output;
}

/*
 * 获取字符在字符串最后出现的位置
 * 参数：被查找的字符串/目标字符
 * 返回值：从0开始的索引
 * -2 字符串超长
 * -1 未找到 
 */
int lastChr(const char *const str, const char chr)
{
    if (strlen(str) > MAX_TEXT_LENGTH)
    {/*字符串长度合法性检查*/
        return -2;
    }
    
    char *ptr = (char *)(str + strlen(str));
    while (*ptr != chr && ptr >= str)
    {
        ptr--;
    }
    
    if (ptr < str)
    {
        return -1;
    }
    else
    {
        return ptr - str;
    }
}

/*
 * 判断字符是否是指定字符之一
 * 参数：输入字符/包含指定字符的字符串
 * 返回值：是否是指定字符之一
 */
BOOL isDesignatedChar(char ch, const char *designatedChar)
{
    char *ptr = (char *)designatedChar;
    while (*ptr != '\0')
    {
        if (*ptr == ch)
        {
            return TRUE;
        }
        ptr++; 
    }
    
    return FALSE;
}

/*
 * 判断字符串中字符是否都是指定字符
 * 参数：输入字符串/包含指定字符的字符串
 * 返回值：是否是指定字符串
 */
BOOL isDesignatedStr(char *str, char *designatedChar)
{
    int cnt = 0;
    int i, j;
    for (i = 0; i < (int)strlen(str); i++)
    {
        for (j = 0; j < (int)strlen(designatedChar); j++)
        {
            if (str[i] == designatedChar[j])
            {
                cnt++;
            }
        }
    }
    
    if (cnt == (int)strlen(str))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
 * 判断一个字符串是否是utf-8编码
 * 参数:要检测的字符串
 * 返回值:是否是utf-8编码 
 */
BOOL isUtf8(char const *const str)
{
    /*非法检查*/
    if (str == NULL)
    {
        return FALSE;
    }
    
    int i, len;
    const unsigned char *ptr = str;
    while ((*ptr) != '\0')
    {
        if (((*ptr) & 0x80) == 0x00)
        {//0000 0000 - 0000 007F    0xxxxxxx
            ptr++;
            continue;
        }
        else if (((*ptr) & 0xE0) == 0xC0)
        {//0000 0080 - 0000 07FF    110xxxxx 10xxxxxx
            len = 1;
        }
        else if (((*ptr) & 0xF0) == 0xE0)
        {//0000 0800 - 0000 FFFF    1110xxxx 10xxxxxx 10xxxxxx
            len = 2;
        }
        else if (((*ptr) & 0xF8) == 0xF0)
        {//0001 0000 - 0010 FFFF    11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            len = 3;
        }
        else if (((*ptr) & 0xFC) == 0xF8)
        {//0020 0000 - 03FF FFFF    111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            len = 4;
        }
        else if (((*ptr) & 0xFE) == 0xFC)
        {//0400 0000 - 7FFF FFFF    1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
            len = 5;
        }
        else
        {
            return FALSE;
        }
        
        for (i = 0; i < len; i++)
        {
            ptr++;
            if (*ptr == '\0' || ((*ptr) & 0xC0) != 0x80)
            {
                return FALSE;
            }
        }
        ptr++;
    }
    
    return TRUE;
}

/* 
 * 安全的字符串复制
 * 参数：目的字符串/源字符串/最大长度
 * 返回值：目的字符串指针
 */
char *strSafeCopy(char *destination, const char *const source, size_t count)
{
    char *returnPtr;
    returnPtr = strncpy(destination, source, count);
    destination[count - 1] = '\0';
    return returnPtr;
}