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

/*
计算字符串高度 
参数：
字符串指针/字号/字体 
返回值：
高度（像素） 
*/
int getStrHei(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
{
	return fontSizeSet + (fontSizeInFile - 25);
}

/*
计算字符串宽度
参数：
字符串指针/字号/字体
返回值：
宽度（像素） 
*/
int getStrLen(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
{
/*
目前仅针对utf-8 
首字节			空间占用		起始 
0--- ---- 		1 byte			0x00 
110- ----		2 byte			0xC0 
1110 ----		3 byte			0xE0
1111 0---		4 byte			0xF0
1111 10--		5 byte			0xF8 
1111 110-		6 byte			0xFC
*/
	int cnt = 0;
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
	return (fontSizeSet + (fontSizeInFile - 25)) / 2 * cnt;
}

/*
字符串（十进制）转化为浮点数
如果有左右括号将忽略
*/
float strToFloat(char *str)
{
	float sum = 0;
	int sign = 1;
	if (*str == '(')
	{
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str != '.')
	{
		if (*str == '\0' || *str == ')')
		{
			return sum * sign;
		}
		sum = sum * 10 + (*str - '0');
		str++;
	}
	str++;
	int cnt = 1;
	while (*str != '\0' && *str != ')')
	{
		sum += pow(0.1, cnt) * (*str - '0');
		cnt++;
		str++;
	}
	return sum * sign;
}

/*
字符串（十进制）转化为整数
如果有左右括号将忽略
*/
int strToInt(char *str)
{
	int sum = 0, sign = 1;
	if (*str == '(')
	{
		str++;
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str != '\0' && *str != ')')
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	return sum * sign;
}

/*
得到字符串左边部分，并移动指针至截断位置后一个字符
参数：输出字符串/输入字符串指针地址/截断位置/ 
返回值：结果字符串地址 
*/
char *strGetLeftPart(char *opStr, char **ipStr, char cutCh)
{
	char *rtStr = opStr;
	while (**ipStr != '\0' && **ipStr != cutCh)
	{
		*opStr = **ipStr;
		opStr++;
		(*ipStr)++;
	}
	if (**ipStr == cutCh)
	{
		(*ipStr)++;
	}
	*opStr = '\0';
	return rtStr;
}

/*
去字符串左右引号，没有的话则不处理
返回值：输入的指针 
*/
char *deQuotMarks(char *str)
{
	char *rtStr = str;
	/*去前引号*/
	if (*str == '\"')
	{/*判断是不是直接的引号*/ 
		while(*(str + 1) != '\0')
		{
			*str = *(str + 1);
			str++;
			
		}
	}
	else if (*str == '&' && *(str + 1) == 'q' && *(str + 2) == 'u' &&
			*(str + 3) == 'o' && *(str + 4) == 't' && *(str + 5) == ';')
	{/*判断是不是引号的转义字符*/ 
		while (*(str + 6) != '\0')
		{
			*str = *(str + 6);
			str++;
		}
	}
	else
	{
		while (*str != '\0')
		{
			str++;
		}
	}
	
	/*去后引号*/
	if (*(str - 1) == '\"')
	{
		*(str - 1) = '\0';
	}
	else if (*(str - 6) == '&' && *(str - 5) == 'q' && *(str - 4) == 'u' &&
			*(str - 3) == 'o' && *(str - 2) == 't' && *(str - 1) == ';')
	{
		*(str - 6) = '\0';
	}
	else
	{
		*str = '\0';
	}
	
	return rtStr;
}

/*
去字符串左右括号，没有的话则不处理
返回值：输入的指针 
*/
char *deBrackets(char *str)
{
	char *rtStr = str;
	/*去前括号*/
	if (*str == '(')
	{
		while (*(str + 1) != '\0')
		{
			*str = *(str + 1);
			str++;
		}
	}
	else
	{
		while (*str != '\0')
		{
			str++;
		}
	}
	
	/*去后括号*/
	if (*(str - 1) == ')')
	{
		*(str - 1) = '\0';
	}
	else
	{
		*str = '\0';
	}
	
	return rtStr;
}

/*
除去指定位置左右空格
参数：
要去空格的字符串/指定的位置地址/
返回值：
结果字符串/
要去指定的字符左右空格可与strchr()函数配合 
*/
char *deDesignatedSpace(char *const str, char *startPtr)
{
	/*非法检查*/
	if (str == NULL || startPtr == NULL)
	{
		return NULL;
	}
	
	char *leftPtr, *rightPtr;
	
	/*去左边的空格*/
	leftPtr = startPtr - 1;
	rightPtr = startPtr;
	while (leftPtr >= str)
	{
		if (*leftPtr != ' ')
		{
			break;
		}
		leftPtr--;
	}
	
	if (leftPtr < startPtr - 1)
	{
		leftPtr++;/*向后移一位移到空格的位置*/
		startPtr = leftPtr;
		while (*rightPtr != '\0')
		{
			*leftPtr = *rightPtr;
			leftPtr++;
			rightPtr++;
		}
		
		*leftPtr = '\0';
	}
	
	/*去右边的空格*/
	leftPtr = rightPtr = startPtr + 1;
	while (*rightPtr != '\0')
	{
		if (*rightPtr != ' ')
		{
			break;
		}
		rightPtr++;
	}
	
	while (*rightPtr != '\0')
	{
		*leftPtr = *rightPtr;
		leftPtr++;
		rightPtr++;
	}
	*leftPtr = '\0';
	return str; 
}

/*
除去字符串左右空格 
参数：
要去空格的字符串/
返回值：
结果字符串/ 
*/
char *deLeftRightSpace(char *const str)
{
	/*非法检查*/
	if (str == NULL)
	{
		return NULL;
	}
	
	int total = 0;
	char *leftPtr, *rightPtr;
	leftPtr = rightPtr = str;
	/*去左边空格*/
	while (*rightPtr == ' ')
	{
		rightPtr++;
	}
	
	while (*rightPtr != '\0')
	{
		*leftPtr = *rightPtr;
		leftPtr++;
		rightPtr++;
	}
	
	/*去右边空格*/
	leftPtr--;
	while (*leftPtr == ' ')
	{
		leftPtr--;
	}
	*(leftPtr + 1) = '\0';
	
	return str; 
}

/*
转换成小写字母
参数：
输出字符串地址/输入字符串地址/ 
返回值：
结果字符串地址
若输出字符串地址为NULL，则将直接修改输入字符串
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
判断字符串中字符是否都是指定字符
输入字符串/包含指定字符的字符串/ 
*/
BOOL isDesignatedChar(char *str, char *designatedChar)
{
	int cnt = 0;
	int i, j;
	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < strlen(designatedChar); j++)
		{
			if (str[i] == designatedChar[j])
			{
				cnt++;
			}
		}
	}
	
	if (cnt == strlen(str))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*
利用WINAPI进行编码相互转换
参数：
原字符串编码/目标字符串编码/输入字符串/输出字符串/输出容器大小（0为不检查）/ 
返回值：
输出字符串/
支持任何系统支持的编码 
opStr 为 NULL 则将结果返回到 ipStr 中，返回值为输入字符串
*/
char *transcoding(UINT sourceCode, UINT targetCoding, char *const ipStr, char *const opStr, int sizeOfOp)
{
	/*非法检查*/
	if (ipStr == NULL)
	{
		return NULL;
	}
	
	int len;
	wchar_t *unicode;
	char *targetStr;
	/*转unicode*/
	len = MultiByteToWideChar(sourceCode, 0, ipStr, -1, NULL, 0);
	if ((unicode = malloc(len * sizeof(wchar_t))) == NULL)
	{
		return NULL;
	}
	
	MultiByteToWideChar(sourceCode, 0, ipStr, -1, unicode, len);
	
	/*转目标编码*/
	len = WideCharToMultiByte(targetCoding, 0, unicode, -1, NULL, 0, NULL, NULL);
	if (sizeOfOp < len && sizeOfOp != 0)/*判断输出容器是否足够大*/
	{
		free(unicode);
		return NULL;
	}
	if ((targetStr = malloc(len * sizeof(char))) == NULL)
	{
		return NULL;
	}
	WideCharToMultiByte(targetCoding, 0, unicode, -1, targetStr, len, NULL, NULL);
	
	/*回收空间返回结果*/
	if (opStr != NULL)
	{
		strcpy(opStr, targetStr);
		free(unicode);
		free(targetStr);
		return opStr;
	}
	else
	{
		strcpy(ipStr, targetStr);
		free(unicode);
		free(targetStr);
		return ipStr;
	}
}

/*
判断一个字符串是否是utf-8
检查字符串是否完全符合utf-8编码规范 
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
    	{//0000 0000 - 0000 007F	0xxxxxxx
    		ptr++;
    		continue;
		}
    	else if (((*ptr) & 0xE0) == 0xC0)
    	{//0000 0080 - 0000 07FF	110xxxxx 10xxxxxx
    		len = 1;
		}
		else if (((*ptr) & 0xF0) == 0xE0)
    	{//0000 0800 - 0000 FFFF	1110xxxx 10xxxxxx 10xxxxxx
    		len = 2;
		}
		else if (((*ptr) & 0xF8) == 0xF0)
    	{//0001 0000 - 0010 FFFF	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    		len = 3;
		}
		else if (((*ptr) & 0xFC) == 0xF8)
    	{//0020 0000 - 03FF FFFF	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
    		len = 4;
		}
		else if (((*ptr) & 0xFE) == 0xFC)
    	{//0400 0000 - 7FFF FFFF	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
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
