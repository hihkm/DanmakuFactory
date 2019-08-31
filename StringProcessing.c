#include "DanmakuFactory.h"

/*
计算字符串高度 
参数：
字符串指针/用户设定文字大小/原弹幕文件中文字大小/字体 
返回值：
高度（像素） 
*/
int GetStrHei(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
{
	return fontSizeSet + (fontSizeInFile - 25);
}

/*
计算字符串宽度
参数：
字符串指针/用户设定文字大小/原弹幕文件中文字大小/字体 
返回值：
宽度（像素） 
*/
int GetStrLen(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName)
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
	while(*str != '\0')
	{
		if(*str >= 0xC0)
		{
			cnt += 2;
		}
		else if(*str < 0x80)
		{
			cnt += 1;
		}
		str++;
	}
	return (fontSizeSet + (fontSizeInFile - 25)) / 2 * cnt;
}

/*
字符串（十进制）转化为浮点数
*/
float StrToFloat(char *str)
{
	float sum = 0;
	int sign = 1;
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	while(*str != '.')
	{
		if(*str == '\0')
		{
			return sum * sign;
		}
		sum = sum * 10 + (*str - '0');
		str++;
	}
	str++;
	int cnt = 1;
	while(*str != '\0')
	{
		sum += pow(0.1, cnt) * (*str - '0');
		cnt++;
		str++;
	}
	return sum * sign;
}

/*
字符串（十进制）转化为整数
*/
int StrToInt(char *str)
{
	int sum = 0, sign = 1;
	if(*str == '-')
	{
		sign = -1;
		str++;
	}
	while(*str != '\0')
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
char *StrGetLeftPart(char *opStr, char **ipStr, char cutCh)
{
	char *rtStr = opStr;
	while(**ipStr != '\0' && **ipStr != cutCh)
	{
		*opStr = **ipStr;
		opStr++;
		(*ipStr)++;
	}
	if(**ipStr == cutCh)
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
char *DeQuotMarks(char *str)
{
	char *rtStr = str;
	/*去前引号*/
	if(*str == '\"')
	{/*判断是不是直接的引号*/ 
		while(*(str + 1) != '\0')
		{
			*str = *(str + 1);
			str++;
			
		}
	}
	else if(*str == '&' && *(str + 1) == 'q' && *(str + 2) == 'u' &&
			*(str + 3) == 'o' && *(str + 4) == 't' && *(str + 5) == ';')
	{/*判断是不是引号的转义字符*/ 
		while(*(str + 6) != '\0')
		{
			*str = *(str + 6);
			str++;
		}
	}
	else
	{
		while(*str != '\0')
		{
			str++;
		}
	}
	
	/*去后引号*/
	if(*(str - 1) == '\"')
	{
		*(str - 1) = '\0';
	}
	else if(*(str - 6) == '&' && *(str - 5) == 'q' && *(str - 4) == 'u' &&
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
