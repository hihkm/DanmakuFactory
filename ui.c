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
显示或隐藏光标 
*/
void showCursor(BOOL show)
{
	CONSOLE_CURSOR_INFO cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
	if (show == TRUE)
	{
		cursor.bVisible = TRUE;
	}
	else
	{
		cursor.bVisible = FALSE;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

/*
设定光标位置
*/
void setPos(int x, int y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

/*
自定义配色的格式输出 
参数：全局配色/设定配色/格式控制字符串/对应内容 
返回值：输出字节数 
*/
int stylePrintf(WORD gobalStyle, WORD printStyle, char *format, ...)
{
	int cnt;	
	va_list arg;
	va_start(arg, format);
	/*修改控制台配色*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), printStyle);
	cnt = vprintf(format, arg);
	va_end(arg);
	/*修改回原来的配色*/ 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gobalStyle);
	return cnt;
}

/*
打印菜单文字 
参数：开始坐标x/开始坐标y/选中项/选中项指针符号/全局配色/选中项配色/是否每行设定样式/行数/各行内容
说明：可变参数值为""/表示跳过该行转向下一行参数selected从0开始且被跳过行不算入
	  如果每行都设定样式则可变参数的每一个参数后面都跟随一个WORD类型的表示配色的参数 
*/
void printMenuText(int x, int y, int selected, char *pointer,
				   WORD gobalStyle, WORD selectedStyle, BOOL allLineSetStyle,
				   int numOfLines, ...)
{
	int cnt, skip = 0;
	char *textOfLine;
	char blank[16] = {0}; 
	va_list arg;
	va_start(arg, numOfLines);
	
	for (cnt=0; cnt<strlen(pointer) && cnt < 16; cnt++)
	{
		blank[cnt] = ' ';
	}
	
	for (cnt=0; cnt<numOfLines; cnt++)
	{
		textOfLine = va_arg(arg, char *);/*读可变参数内容*/
		setPos(x, y);/*定位*/
		
		if (textOfLine[0] == '\0')
		{/*空行*/
			skip++;
		}
		else if (cnt + skip == selected)
		{/*被选中项*/
			if (selectedStyle != 0x00)
			{
				if (allLineSetStyle == TRUE)
				{
					va_arg(arg, int);/*跳过一个控制颜色的参数*/
				}
				stylePrintf(gobalStyle, selectedStyle, "%s%s", pointer, textOfLine);
			}
			else if (allLineSetStyle == TRUE)
			{
				stylePrintf(gobalStyle, (WORD)(va_arg(arg, int)), "%s%s", pointer, textOfLine);
			}
			else
			{
				stylePrintf(gobalStyle, gobalStyle, "%s%s", pointer, textOfLine);
			}	
		}
		else if (allLineSetStyle == TRUE)
		{/*普通行 但定义每一行的颜色*/
			stylePrintf(gobalStyle, (WORD)(va_arg(arg, int)), "%s%s", blank, textOfLine);
		}
		else
		{/*普通行 不定义每一行的颜色*/ 
			stylePrintf(gobalStyle, gobalStyle, "%s%s", blank, textOfLine);
		}
		y++;/*移动行光标*/
	}
	va_end(arg);
}

/*
引导用户输入一个特定范围的整数
参数：
左范围/右范围/格式控制字符串/对应内容 
返回值：
得到的值 
*/
int inputInt(int rangeLeft, int rangeRight, char *msgFormat, ...)
{
	char tempText[MAX_TEXT_LENGTH];
	int getNum;
	va_list arg;
	va_start(arg, msgFormat);
	do {
		fflush(stdin);
		vprintf(msgFormat, arg);
		fgets(tempText, MAX_TEXT_LENGTH, stdin);
		if(tempText[strlen(tempText) - 1] == '\n')
		{/*先获取字符串判断是否有非法字符*/
			tempText[strlen(tempText) - 1] = '\0';
		}
		getNum = strToInt(tempText);
	} while (getNum < rangeLeft || getNum > rangeRight || !isDesignatedChar(tempText, "-0123456789"));
	
	va_end(arg);
	return getNum;
}
