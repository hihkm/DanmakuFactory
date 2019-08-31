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

#include "DanmakuFactory.h"
#include "DanmakuConvert.h"
#include "ui.c"
#include "ReadFile.c"
#include "WriteFile.c"
#include "StringProcessing.c" 
#include "ListProcessing.c"

int main(int argc, char **argv)
{
	int cnt;
	char key;/*从键盘获取的键值*/ 
	char firSelected, secSelected, thiSelected;/*一二三级菜单已选择项*/ 
	
	char tempText[MAX_TEXT_LENGTH];
	
	FILE *configFilePtr;/*配置文件指针*/ 
	CONFIG defaultConfig;/*默认配置*/
	CONFIG *inputFile = NULL;/*对输入的配置*/ 
	char configFilePath[MAX_TEXT_LENGTH];/*配置文件路径*/ 
	
	/*winAPI读写ini不支持相对路径 将相对路径转换为绝对路径*/
	getcwd(configFilePath, MAX_TEXT_LENGTH);
	sprintf(configFilePath, "%s\\DanmakuFactoryConfig.ini", configFilePath);
	
	/*读取配置文件*/
	readConfigFile(&defaultConfig, configFilePath);
	if (!access("DanmakuFactoryConfig.bin", 0))
	{/*二进制配置文件兼容*/
		printf("DanmakuFactory v%s\n", VERSION);
		printf("\n--------------------------------------------------------"
			   "\n[!] 检查到旧版本配置文件DanmakuFactoryConfig.bin"
			   "\n    原二进制配置文件不再受支持"
			   "\n    请输入Y或y转换为新版本 原配置文件将会被删除"
			   "\n--------------------------------------------------------"
			   "\n请选择 ");
		firSelected = getchar();
		if((configFilePtr = fopen("DanmakuFactoryConfig.bin", "rb")) != NULL)
		{
			OLDCONFIG oldConfig;
			fread(&oldConfig, sizeof(oldConfig), 1, configFilePtr);
			defaultConfig.resX = oldConfig.resX;
			defaultConfig.resY = oldConfig.resY;
			defaultConfig.rollTime = oldConfig.rollTime;
			defaultConfig.holdTime = oldConfig.holdTime;
			defaultConfig.density = oldConfig.density;
			defaultConfig.outline = oldConfig.outline;
			defaultConfig.shadow = oldConfig.shadow;
			defaultConfig.fontSize = oldConfig.fontSize;
			defaultConfig.blank = oldConfig.blank;
			strcpy(defaultConfig.fontName, oldConfig.fontName);
			strcpy(defaultConfig.blockMode, oldConfig.blockMode);
			strcpy(defaultConfig.debugMode, oldConfig.debugMode);
			fclose(configFilePtr);
		}
		else
		{
			firSelected = 'n';
			printf("[X] 读取原配置文件失败\n");
		}
		
		if (firSelected == 'Y' || firSelected == 'y')
		{
			if (writeConfigFile(defaultConfig, configFilePath) == FALSE)
			{
				printf("[X] 写配置文件失败 没有进行任何文件修改\n");
			}
			else
			{
				if (remove("DanmakuFactoryConfig.bin"))
				{
					printf("[!] 原配置文件删除失败 请手动删除\n");
				}
				else
				{
					printf("[!] 转换完成 原配置文件已删除\n");
				}
			}
			system("pause");
		}
		else
		{
			printf("   没有进行任何文件修改\n"); 
		}
	}
	
	/*转换任务*/
	if (argc == 1)
	{/*直接运行*/
		/*读取配置文件用户设定的缓冲区大小 应当属于ProgramSet*/
		int bufferX = GetPrivateProfileInt("ProgramSet", "bufferX", 0, configFilePath);
		int bufferY = GetPrivateProfileInt("ProgramSet", "bufferY", 0, configFilePath);
		if (bufferX == 0 || bufferY == 0)
		{/*如果用户写到了DanmakuSet也同样可以读出来*/
			bufferX = GetPrivateProfileInt("DanmakuSet", "bufferX", 512, configFilePath);
			bufferY = GetPrivateProfileInt("DanmakuSet", "bufferY", 2096, configFilePath);
		}
		/*设定缓冲区大小*/
		sprintf(tempText, "mode con cols=%d lines=%d", bufferX, bufferY);
		system(tempText);
		
		/*读取配置文件用户设定的窗体大小 应当属于ProgramSet*/
		int windowX = GetPrivateProfileInt("ProgramSet", "windowX", 0, configFilePath);
		int windowY = GetPrivateProfileInt("ProgramSet", "windowY", 0, configFilePath);
		if (windowX == 0 || windowY == 0)
		{/*如果用户写到了DanmakuSet也同样可以读出来*/
			windowX = GetPrivateProfileInt("DanmakuSet", "windowX", GetSystemMetrics(SM_CXSCREEN)/2, configFilePath);
			windowY = GetPrivateProfileInt("DanmakuSet", "windowY", GetSystemMetrics(SM_CYSCREEN)/1.5, configFilePath);
		}
		/*设定窗口大小*/
		MoveWindow(GetConsoleWindow(), 
				   (GetSystemMetrics(SM_CXSCREEN) - windowX) / 2,
				   (GetSystemMetrics(SM_CYSCREEN) - windowY) / 2,
				   windowX, windowY, TRUE);
		/*禁止拖动改变窗口大小*/
		SetWindowLongPtr(GetConsoleWindow(), GWL_STYLE, 
			  GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
		
		MAINPAGE:
		system("cls");
		showCursor(FALSE);/*隐藏指针*/
		
		printf("DanmakuFactory v%s\n", VERSION);
		printf("--------------------------------"
			   "\n\n\n\n"
			   "--------------------------------"
			   "\n↑↓或选项前序号选择 ENTER确定"
			   );
		
		key = 0;
		firSelected = 0;
		while (key != ENTER)
		{
			printMenuText(2, 2, firSelected, "> ", 0x0F, 0xF0, FALSE, 3,
						  "0 开始转换          ",
						  "1 更新与帮助        ",
						  "2 退出              "
						);
			fflush(stdin);
			key = getch();
			fflush(stdin);
			if (key == UP)
			{
				if (firSelected == 0)
				{
					firSelected = 2;
				}
				else
				{
					firSelected--;
				}
			}
			else if (key == DOWN)
			{
				if (firSelected == 2)
				{
					firSelected = 0;
				}
				else
				{
					firSelected++;
				}
			}
			else if (key >= '0' && key <= '2')
			{
				firSelected = key - '0';
			}
		}
		
		showCursor(TRUE);/*显示指针*/
		if (firSelected == 0)
		{/*简单转换*/
			int i = 0;
			system("cls");
			printf("DanmakuFactory v%s\n", VERSION);
			printf("--------------------------------");
			printf("\n请输入要转换的文件的路径\n");
			do {
				if (i % 16 == 0)
				{
					/*申请用于存放路径的内存*/
					if ((inputFile = (CONFIG *)realloc(inputFile, (i+16)*sizeof(CONFIG))) == NULL)
					{
						printf("\n[X] 内存申请失败\n");
						system("pause");
						exit(1);
					}
				}
				
				/*赋予初值*/
				inputFile[i] = defaultConfig;/*必须先读全部值再将不能直接读初值的内容赋值*/
				//strcpy(inputFile[i].outputFormat, "ass");
				
				inputFile[i].timeShift = 0.00;
				
				/*输入输入文件路径*/
				if (i == 1)
				{
					printf("继续输入文件路径以批量转换或输入回车结束\n");
				}
				printf("%d > ", i + 1);
				fgets(inputFile[i].input, MAX_TEXT_LENGTH, stdin);
				if((inputFile[i].input)[strlen(inputFile[i].input) - 1] == '\n')
				{
					(inputFile[i].input)[strlen(inputFile[i].input) - 1] = '\0';
				}
				deQuotMarks(inputFile[i].input);
				sprintf(inputFile[i].output, "%s.%s", inputFile[i].input, "ass");/*生成输出文件路径*/ 
				
				i++;
			} while ((inputFile[i - 1].input)[0] != '\0');
			i--;/*最后一个没有数据所以丢弃*/
			
			/*没有任何数据就直接返回*/ 
			if (i == 0)
			{
				free(inputFile);
				inputFile = NULL;/*不重置下次realloc就会出错*/
				goto MAINPAGE;
			}
			
			/*设定页*/
			int nowFile = 0;
			int page = 0;
			secSelected = 6;
			
			/*只有一条数据就没有分开全部与第一条的意义了*/
			if (i == 1)
			{
				nowFile = 1;
			}
			
			while (TRUE)
			{
				char displayText[4][MAX_TEXT_LENGTH];/*前8行给目录显示 后面的给菜单*/
				
				key = 0;
				system("cls");
				showCursor(FALSE);/*隐藏指针*/
				
				/*打印界面*/ 
				printf("DanmakuFactory v%s\n", VERSION);
				printf("\n共接收到 %d 个文件", i);
				printf("\n--------------------------------");
				printf("\n\n\n\n\n\n\n\n");
				printf("\n←上一页   →下一页"
					   "\n--------------------------------"
					   );
				printf("\n"
					   "\n"
					   "\n"
					   "\n"
					   "\n"
					   "\n"
					   "\n" 
					   "\n--------------------------------"
					   "\n↑↓选择  ENTER进入"
					   );
				
				/*打印当前页能显示的文件列表*/ 
				for (cnt = 0; cnt < 8 && page * 8 + cnt < i; cnt++)
				{
					setPos(0, 4 + cnt);
					printf("%d %s", page*8 + cnt + 1, inputFile[page*8 + cnt].input);
				}
				setPos(21, 12);
				printf("第%d页 共%d页", page + 1, (int)(ceil(i / 8.0))); 
				
				/*菜单栏需要显示的文本 填充到数组displayText*/
				if (nowFile == 0)
				{
					sprintf(displayText[0], "1 当前设置 全部文件");
					sprintf(displayText[1], "2 转换为 --");
					sprintf(displayText[2], "3 时轴偏移 %.2f", inputFile[0].timeShift);
					for (cnt = 1; cnt < i; cnt++)
					{
						if (fabs(inputFile[cnt].timeShift - inputFile[cnt - 1].timeShift) > FLOAT_EPS)
						{
							sprintf(displayText[2], "3 时轴偏移 --");
							break;
						}
					}
					
					if (inputFile[0].outputEncoding == ANSI)
					{
						sprintf(displayText[3], "4 输出编码 ANSI");
					}
					else
					{
						sprintf(displayText[3], "4 输出编码 UTF-8");
					}
					
					for (cnt = 1; cnt < i; cnt++)
					{
						if (inputFile[cnt].outputEncoding != inputFile[cnt - 1].outputEncoding)
						{
							sprintf(displayText[3], "4 输出编码 --");
							break;
						}
					}
				}
				else
				{
					sprintf(displayText[0], "1 当前设置 %d", nowFile);
					sprintf(displayText[1], "2 转换为 %s", inputFile[nowFile - 1].output);
					sprintf(displayText[2], "3 时轴偏移 %.2f", inputFile[nowFile - 1].timeShift);
					if (inputFile[nowFile - 1].outputEncoding == ANSI)
					{
						sprintf(displayText[3], "4 输出编码 ANSI");
					}
					else
					{
						sprintf(displayText[3], "4 输出编码 UTF-8");
					}
				}
				
				
				/*获取键盘输入*/ 
				while (key != ENTER)
				{
					if (key == UP)
					{
						if (secSelected == 0)
						{
							secSelected = 6;
						}
						else
						{
							secSelected--;
						}
					}
					else if (key == DOWN)
					{
						if (secSelected == 6)
						{
							secSelected = 0;
						}
						else
						{
							secSelected++;
						}
					}
					else if (key == LEFT || key == RIGHT)
					{
						if (key == LEFT)
						{
							if (page == 0)
							{
								page = (int)(ceil(i / 8.0)) - 1;/*向上取整*/
							}
							else
							{
								page--;
							}
						}
						else
						{
							if (page == (int)(ceil(i / 8.0)) - 1)
							{
								page = 0;/*向上取整*/
							}
							else
							{
								page++;
							}
						}
						break;/*跳出循环然后刷新整个页面*/	
					}
					else if (key == '0')
					{
						secSelected = 6;
					}
					else if (key >= '1' && key <= '6')
					{
						secSelected = key - '0' - 1;
					}
					
					/*打印菜单*/
					printMenuText(0, 14, secSelected, "> ", 0x0F, 0xF0, FALSE, 7,
								  displayText[0],
								  displayText[1],
								  displayText[2],
								  displayText[3],
								  "5 更多弹幕设置",
								  "6 保存当前设置", 
								  "0 开始全部转换"
								 );
					fflush(stdin);
					key = getch();
					fflush(stdin);
				}/*结束菜单选择循环*/ 
				
				if (key == LEFT || key == RIGHT)
				{/*如果翻页则直接刷新整个页面*/
					continue;
				}
				
				showCursor(TRUE);/*显示指针*/
				/*根据用户选择的进一步操作*/
				if (secSelected == 0)
				{/*设置当前要设置的文件*/
					setPos(0, 22);
					if (i == 1)
					{
						printf("[!] 当前项无法设置，因为只有一个文件\n");
						system("pause"); 
					}
					else
					{
						printf("请输入你要设置的文件前序号 0表示全部\n");
						do {
							fflush(stdin);
							printf("请输入(0-%d) ", i);
							fgets(tempText, MAX_TEXT_LENGTH, stdin);
							if(tempText[strlen(tempText) - 1] == '\n')
							{
								tempText[strlen(tempText) - 1] = '\0';
							}
							nowFile = strToInt(tempText);/*先获取字符串判断是否有非法字符*/
						} while ((nowFile < 0 || nowFile > i) && !isDesignatedChar(tempText, "0123456789"));
					}
				}
				else if (secSelected == 1)
				{/*设置文件路径*/ 
					setPos(0, 22);
					if (nowFile == 0)
					{/*全部设置会导致错误*/
						printf("[X] 不能同时设定全部文件的输出路径\n");
						system("pause"); 
					}
					else
					{/*局部设置*/ 
						printf("请输入 %d 号文件的输出路径\n", nowFile);
						printf("请输入(含后缀名) ");
						fgets(inputFile[nowFile - 1].output, MAX_TEXT_LENGTH, stdin);
						if((inputFile[nowFile - 1].output)[strlen(inputFile[nowFile - 1].output) - 1] == '\n')
						{
							(inputFile[nowFile - 1].output)[strlen(inputFile[nowFile - 1].output) - 1] = '\0';
						}
						deQuotMarks(inputFile[nowFile - 1].output);
					}
				}
				else if (secSelected == 2)
				{/*设置时轴偏移量*/ 
					setPos(0, 22);
					if (nowFile == 0)
					{/*全部设置*/ 
						printf("请输入全部文件的时轴偏移\n", nowFile);
						do {
							printf("请输入(小数) ");
							fgets(tempText, MAX_TEXT_LENGTH, stdin);
							if(tempText[strlen(tempText) - 1] == '\n')
							{
								tempText[strlen(tempText) - 1] = '\0';
							}
						} while (!isDesignatedChar(tempText, "-.0123456789"));/*判断是否有非法字符*/
						float tempTimeShift = strToFloat(tempText);
						for (cnt = 0; cnt < i; cnt++)
						{
							inputFile[cnt].timeShift = tempTimeShift;
						}
						
					}
					else
					{/*局部设置*/
						printf("请输入 %d 号文件的时轴偏移\n", nowFile);
						do {
							printf("请输入(小数) ");
							fgets(tempText, MAX_TEXT_LENGTH, stdin);
							if(tempText[strlen(tempText) - 1] == '\n')
							{
								tempText[strlen(tempText) - 1] = '\0';
							}
						} while (!isDesignatedChar(tempText, "-.0123456789"));/*判断是否有非法字符*/ 
						inputFile[nowFile - 1].timeShift = strToFloat(tempText);
					}
					
				}
				else if (secSelected == 3)
				{/*设置输出编码*/ 
					setPos(0, 22);
					showCursor(FALSE);/*隐藏指针*/
					if (nowFile == 0)
					{/*设置全部*/ 
						printf("请选择全部文件的输出编码\n", nowFile);
					}
					else
					{/*设置单个*/ 
						printf("请选择 %d 号文件的输出编码\n", nowFile);
					}
					
					/*通过选择菜单选择一个项*/
					key = 0;
					thiSelected = 0; 
					while (key != ENTER)
					{
						printMenuText(0, 23, thiSelected, "> ", 0x0F, 0xF0, FALSE, 2,
									  "0 ANSI           ",
									  "1 UTF-8          ");
						printf("\n\n[!] 目前的编码转换并不完全可靠");
						printf("\n    已知GB2312转UTF-8有几率发生崩溃");
						printf("\n    相关编码转换建议在文本编辑器完成");
						fflush(stdin);
						key = getch();
						fflush(stdin);
						if (key == UP)
						{
							if (thiSelected == 0)
							{
								thiSelected = 1;
							}
							else
							{
								thiSelected--;
							}
						}
						else if (key == DOWN)
						{
							if (thiSelected == 1)
							{
								thiSelected = 0;
							}
							else
							{
								thiSelected++;
							}
						}
						else if (key >= '0' && key <= '1')
						{
							thiSelected = key - '0';
						}
					}/*结束编码选择菜单*/ 
					 
					/*响应用户的选择*/ 
					if (thiSelected == 0)
					{
						if (nowFile == 0)
						{/*全部修改*/ 
							for (cnt = 0; cnt < i; cnt++)
							{
								inputFile[cnt].outputEncoding = ANSI;
							}
						}
						else
						{/*局部修改*/
							inputFile[nowFile - 1].outputEncoding = ANSI;
						}
						
					}
					else
					{
						if (nowFile == 0)
						{/*全部修改*/ 
							for (cnt = 0; cnt < i; cnt++)
							{
								inputFile[cnt].outputEncoding = UTF_8;
							}
						}
						else
						{/*局部修改*/ 
							inputFile[nowFile - 1].outputEncoding = UTF_8;
						}
					}
				}
				else if (secSelected == 4)
				{/*其他弹幕设置*/ 
					char setDisplay[20][MAX_TEXT_LENGTH];
					CONFIG newSet;
					
					/*
					读取指定文件的弹幕设置
					数组下标从0开始，nowFile从1开始，因此对某一个文件要减 1
					由于0表示全部 因此nowFile 为 0 时默认取第一个文件无需减 1
					*/
					int dSetSelected = 0;
					int dSetKey; 
					int shift = 1;
					if (nowFile == 0)
					{
						shift = 0;
					}
					
					/*设定页面UI*/
					do {
						system("cls");
						dSetKey = 0;
						showCursor(FALSE);/*隐藏指针*/
						printf("> DanmakuFactory 弹幕设置", nowFile);
						sprintf(setDisplay[0], "   1 分辨率宽 %dpx", inputFile[nowFile - shift].resX);
						sprintf(setDisplay[1], "   2 分辨率高 %dpx", inputFile[nowFile - shift].resY);
						sprintf(setDisplay[2], "   3 滚动弹幕时间 %d秒", inputFile[nowFile - shift].rollTime);
						sprintf(setDisplay[3], "   4 固定弹幕时间 %d秒", inputFile[nowFile - shift].holdTime);
						if (inputFile[nowFile - shift].density == -1)
						{
							sprintf(setDisplay[4], "   5 弹幕密度 不重叠(-1)");
						}
						else if (inputFile[nowFile - shift].density == 0)
						{
							sprintf(setDisplay[4], "   5 弹幕密度 无限制(0)");
						}
						else
						{
							sprintf(setDisplay[4], "   5 弹幕密度 %d条", inputFile[nowFile-shift].density);
						}
						sprintf(setDisplay[5], "   6 文字大小 %d", inputFile[nowFile - shift].fontSize);
						if (isUtf8(defaultConfig.fontName) == TRUE)
						{/*对字体说明文本*/
							transcoding(UTF_8, ANSI, inputFile[nowFile - shift].fontName, NULL, 0);
						}
						sprintf(setDisplay[6], "   7 字体 %s", inputFile[nowFile - shift].fontName);
						sprintf(setDisplay[7], "   8 描边 %d", inputFile[nowFile - shift].outline);
						sprintf(setDisplay[8], "   9 阴影 %d", inputFile[nowFile - shift].shadow);
						sprintf(setDisplay[9], "   a 不透明度 %d", inputFile[nowFile - shift].opacity);
						sprintf(setDisplay[10], "   b 下部留白 %dpx", inputFile[nowFile - shift].blank);
						if ((inputFile[nowFile - shift].blockMode)[0] == '0')
						{
							sprintf(setDisplay[11], "   c 右左滚动[不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[11], "   c 右左滚动[屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[1] == '0')
						{
							sprintf(setDisplay[12], "   d 左右滚动[不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[12], "   d 左右滚动[屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[2] == '0')
						{
							sprintf(setDisplay[13], "   e 顶部固定[不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[13], "   e 顶部固定[屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[3] == '0')
						{
							sprintf(setDisplay[14], "   f 底部固定[不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[14], "   f 底部固定[屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[4] == '0')
						{
							sprintf(setDisplay[15], "   g 特殊    [不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[15], "   g 特殊    [屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[5] == '0')
						{
							sprintf(setDisplay[16], "   h 彩色    [不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[16], "   h 彩色    [屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].blockMode)[6] == '0')
						{
							sprintf(setDisplay[17], "   i 内容重复[不屏蔽]");
						}
						else
						{
							sprintf(setDisplay[17], "   i 内容重复[屏蔽]");
						}
						
						if ((inputFile[nowFile - shift].debugMode)[0] == '0')
						{
							sprintf(setDisplay[18], "   j 数据表格[关闭]");
						}
						else
						{
							sprintf(setDisplay[18], "   j 数据表格[开启]");
						}
						
						if ((inputFile[nowFile - shift].debugMode)[1] == '0')
						{
							sprintf(setDisplay[19], "   k 统计图  [关闭]");
						}
						else
						{
							sprintf(setDisplay[19], "   k 统计图  [开启]");
						}
						
						if (nowFile == 0)
						{/*设置全部*/
							printf("(全部文件)\n");
							/*检查所有文件设置是否相同 不同的置--*/ 
							for (cnt = 1; cnt < i; cnt++)
							{
								if (inputFile[cnt].resX != inputFile[cnt - 1].resX)
								{
									sprintf(setDisplay[0], "   1 分辨率宽 --");
								}
								if (inputFile[cnt].resY != inputFile[cnt - 1].resY)
								{
									sprintf(setDisplay[1], "   2 分辨率宽 --");
								}
								if (inputFile[cnt].rollTime != inputFile[cnt - 1].rollTime)
								{
									sprintf(setDisplay[2], "   3 滚动弹幕时间 --");
								}
								if (inputFile[cnt].holdTime != inputFile[cnt - 1].holdTime)
								{
									sprintf(setDisplay[3], "   4 固定弹幕时间 --");
								}
								if (inputFile[cnt].density != inputFile[cnt - 1].density)
								{
									sprintf(setDisplay[4], "   5 弹幕密度 --");
								}
								if (inputFile[cnt].fontSize != inputFile[cnt - 1].fontSize)
								{
									sprintf(setDisplay[5], "   6 文字大小 --");
								}
								if (strcmp(inputFile[cnt].fontName, inputFile[cnt - 1].fontName))
								{
									sprintf(setDisplay[6], "   7 字体 --");
								}
								if (inputFile[cnt].outline != inputFile[cnt - 1].outline)
								{
									sprintf(setDisplay[7], "   8 描边 --");
								}
								if (inputFile[cnt].shadow != inputFile[cnt - 1].shadow)
								{
									sprintf(setDisplay[8], "   9 阴影 --");
								}
								if (inputFile[cnt].opacity != inputFile[cnt - 1].opacity)
								{
									sprintf(setDisplay[9], "   a 不透明度 --");
								}
								if (inputFile[cnt].blank != inputFile[cnt - 1].blank)
								{
									sprintf(setDisplay[10], "   b 下部留白 --");
								}
								if ((inputFile[cnt].blockMode)[0] != 
									(inputFile[cnt - 1].blockMode)[0])
								{
									sprintf(setDisplay[11], "   c 右左滚动 --");
								}
								if ((inputFile[cnt].blockMode)[1] != 
									(inputFile[cnt - 1].blockMode)[1])
								{
									sprintf(setDisplay[12], "   d 左右滚动 --");
								}
								if ((inputFile[cnt].blockMode)[2] != 
									(inputFile[cnt - 1].blockMode)[2])
								{
									sprintf(setDisplay[13], "   e 顶部固定 --");
								}
								if ((inputFile[cnt].blockMode)[3] != 
									(inputFile[cnt - 1].blockMode)[3])
								{
									sprintf(setDisplay[14], "   f 底部固定 --");
								}
								if ((inputFile[cnt].blockMode)[4] != 
									(inputFile[cnt - 1].blockMode)[4])
								{
									sprintf(setDisplay[15], "   g 特殊     --");
								}
								if ((inputFile[cnt].blockMode)[5] != 
									(inputFile[cnt - 1].blockMode)[5])
								{
									sprintf(setDisplay[16], "   h 彩色     --");
								}
								if ((inputFile[cnt].blockMode)[6] != 
									(inputFile[cnt - 1].blockMode)[6])
								{
									sprintf(setDisplay[17], "   i 内容重复 --");
								}
								if ((inputFile[cnt].debugMode)[0] != 
									(inputFile[cnt - 1].debugMode)[0])
								{
									sprintf(setDisplay[18], "   j 数据表格 --");
								}
								if ((inputFile[cnt].debugMode)[1] != 
									(inputFile[cnt - 1].debugMode)[1])
								{
									sprintf(setDisplay[19], "   k 统计图   --");
								}
							}
						}
						else
						{/*设置单个*/ 
							printf("(%d号文件)\n", nowFile);
						}
						printf("--------------------------------\n");
						
						while (dSetKey != ENTER)
						{
							if (dSetKey == UP)
							{
								if (dSetSelected == 0)
								{
									dSetSelected = 23;
								}
								else
								{
									dSetSelected--;
								}
							}
							else if (dSetKey == DOWN)
							{
								if (dSetSelected == 23)
								{
									dSetSelected = 0;
								}
								else
								{
									dSetSelected++;
								}
							}
							else if (dSetKey >= '1' && dSetKey <= '9')
							{
								dSetSelected = dSetKey - '0';
							}
							else if (dSetKey >= 'a' && dSetKey <= 'b')
							{
								dSetSelected = dSetKey - 'a' + 10;
							}
							else if (dSetKey >= 'c' && dSetKey <= 'i')
							{
								dSetSelected = dSetKey - 'c' + 13;
							}
							else if (dSetKey >= 'j' && dSetKey <= 'k')
							{
								dSetSelected = dSetKey - 'j' + 21;
							}
							else if (dSetKey == '0')
							{
								dSetSelected = 23;
							}
										
							printMenuText(0, 2, dSetSelected, "> ", 0x0F, 0xF0, FALSE, 24,
										  "常规设定",
										  setDisplay[0], setDisplay[1], setDisplay[2],
										  setDisplay[3], setDisplay[4], setDisplay[5],
										  setDisplay[6], setDisplay[7], setDisplay[8],
										  setDisplay[9], setDisplay[10],
										  "按类型屏蔽", setDisplay[11], setDisplay[12],
										  setDisplay[13], setDisplay[14], setDisplay[15],
										  setDisplay[16], setDisplay[17],
										  "调试模式",
										  setDisplay[18], setDisplay[19],
										  "0 完成并退出");
							printf("\n--------------------------------");
							printf("\n↑↓或选项前序号选择 ENTER修改");
							fflush(stdin);
							dSetKey = getch();
							fflush(stdin);
						}
						
						/*执行选择*/
						setPos(0, 27);
						
						showCursor(TRUE);/*显示指针*/
						if (dSetSelected == 1)
						{
							printf("设定新的分辨率宽(px)            \n");						
							inputFile[nowFile - shift].resX = inputInt(1, INT_MAX, "请输入(>0) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].resX = inputFile[0].resX;
								}
							}
						}
						else if (dSetSelected == 2) 
						{
							printf("设定新的分辨率高(px)            \n");
							inputFile[nowFile - shift].resY = inputInt(1, INT_MAX, "请输入(>0) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].resY = inputFile[0].resY;
								}
							}
						}
						else if (dSetSelected == 3) 
						{
							printf("设定新的滚动弹幕滚动速度(秒)    \n");
							inputFile[nowFile - shift].rollTime = inputInt(1, INT_MAX, "请输入(>0) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].rollTime = inputFile[0].rollTime;
								}
							}
						}
						else if (dSetSelected == 4) 
						{
							printf("设定新的固定弹幕停留时间(秒)    \n");
							inputFile[nowFile - shift].holdTime = inputInt(1, INT_MAX, "请输入(>0) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].holdTime = inputFile[0].holdTime;
								}
							}
						}
						else if (dSetSelected == 5) 
						{
							printf("设定新的弹幕密度(条)(0 表示无限制 -1 表示不重叠)\n");
							inputFile[nowFile - shift].density = inputInt(-1, INT_MAX, "请输入(>=-1) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].density = inputFile[0].density;
								}
							}
						}
						else if (dSetSelected == 6) 
						{
							printf("设定新的文字大小                \n");
							inputFile[nowFile - shift].fontSize = inputInt(1, INT_MAX, "请输入(>0) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].fontSize = inputFile[0].fontSize;
								}
							}
						}
						else if (dSetSelected == 7) 
						{
							printf("设定新的字体                    \n请输入 ");
							fgets(inputFile[nowFile - shift].fontName, MAX_TEXT_LENGTH, stdin);
							if(tempText[strlen(inputFile[nowFile - shift].fontName) - 1] == '\n')
							{
								tempText[strlen(inputFile[nowFile - shift].fontName) - 1] = '\0';
							}
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									strcpy(inputFile[cnt].fontName, inputFile[0].fontName);
								}
							}
						}
						else if (dSetSelected == 8) 
						{
							printf("设定新的描边粗细(0 关闭)        \n");
							inputFile[nowFile - shift].outline = inputInt(0, 4, "请输入(0-4) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].outline = inputFile[0].outline;
								}
							}
						}
						else if (dSetSelected == 9) 
						{
							printf("设定新的阴影大小(0 关闭)        \n");
							inputFile[nowFile - shift].shadow = inputInt(0, 4, "请输入(0-4) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].shadow = inputFile[0].shadow;
								}
							}
						}
						else if (dSetSelected == 10) 
						{
							printf("设定新的不透明度(0 完全透明 255 不透明)\n");
							inputFile[nowFile - shift].opacity = inputInt(0, 255, "请输入(0-255) ");
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].opacity = inputFile[0].opacity;
								}
							}
						}
						else if (dSetSelected == 11) 
						{
							printf("设定新的下部留白区域大小（防挡字幕）\n");
							inputFile[nowFile - shift].blank = inputInt(0,
													inputFile[nowFile - shift].resY,
													 "请输入(0-%d) ", inputFile[nowFile - shift].resY);
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blank = inputFile[0].blank;
								}
							}
						}
						else if (dSetSelected == 13) 
						{
							if (inputFile[nowFile - shift].blockMode[0] == '0')
							{
								inputFile[nowFile - shift].blockMode[0] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[0] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[0] = inputFile[0].blockMode[0];
								}
							}
						}
						else if (dSetSelected == 14) 
						{
							if (inputFile[nowFile - shift].blockMode[1] == '0')
							{
								inputFile[nowFile - shift].blockMode[1] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[1] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[1] = inputFile[0].blockMode[1];
								}
							}
						}
						else if (dSetSelected == 15) 
						{
							if (inputFile[nowFile - shift].blockMode[2] == '0')
							{
								inputFile[nowFile - shift].blockMode[2] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[2] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[2] = inputFile[0].blockMode[2];
								}
							}
						}
						else if (dSetSelected == 16) 
						{
							if (inputFile[nowFile - shift].blockMode[3] == '0')
							{
								inputFile[nowFile - shift].blockMode[3] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[3] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[3] = inputFile[0].blockMode[3];
								}
							}
						}
						else if (dSetSelected == 17) 
						{
							if (inputFile[nowFile - shift].blockMode[4] == '0')
							{
								inputFile[nowFile - shift].blockMode[4] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[4] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[4] = inputFile[0].blockMode[4];
								}
							}
						}
						else if (dSetSelected == 18) 
						{
							if (inputFile[nowFile - shift].blockMode[5] == '0')
							{
								inputFile[nowFile - shift].blockMode[5] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[5] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[5] = inputFile[0].blockMode[5];
								}
							}
						}
						else if (dSetSelected == 19) 
						{
							if (inputFile[nowFile - shift].blockMode[6] == '0')
							{
								inputFile[nowFile - shift].blockMode[6] = '1';
							}
							else
							{
								inputFile[nowFile - shift].blockMode[6] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].blockMode[6] = inputFile[0].blockMode[6];
								}
							}
						}
						else if (dSetSelected == 21) 
						{
							if (inputFile[nowFile - shift].debugMode[0] == '0')
							{
								inputFile[nowFile - shift].debugMode[0] = '1';
							}
							else
							{
								inputFile[nowFile - shift].debugMode[0] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].debugMode[0] = inputFile[0].debugMode[0];
								}
							}
						}
						else if (dSetSelected == 22) 
						{
							if (inputFile[nowFile - shift].debugMode[1] == '0')
							{
								inputFile[nowFile - shift].debugMode[1] = '1';
							}
							else
							{
								inputFile[nowFile - shift].debugMode[1] = '0';
							}
							
							if (nowFile == 0)
							{/*全部设置需要将第一个文件拷贝到全部文件*/
								for (cnt = 1; cnt < i; cnt++)
								{
									inputFile[cnt].debugMode[1] = inputFile[0].debugMode[1];
								}
							}
						}
					} while (dSetSelected != 23);
				}
				else if (secSelected == 5)
				{/*保存设置*/
					setPos(0, 22);
					if (nowFile == 0)
					{/*选择全部则保存第一个文件的设置*/
						if (writeConfigFile(inputFile[0], configFilePath))
						{
							printf("[!] 保存成功                    \n");
						}
						else
						{
							printf("[X] 保存失败                    \n");
						}
					}
					else
					{
						if (writeConfigFile(inputFile[nowFile - 1], configFilePath))
						{
							printf("[!] 保存成功                    \n");
						}
						else
						{
							printf("[X] 保存失败                    \n");
						}
					}
					system("pause");
				}
				else if (secSelected == 6)
				{/*开始转换*/
					break;
				}
			}/*结束设定页*/ 
			
			/*转换*/
			int failNum = 0, existNum = 0;
			system("cls");
			printf("DanmakuFactory v%s\n", VERSION);
			printf("--------------------------------");
			printf("\n> 正在检查输出文件是否存在");
			for (cnt = 0; cnt < i; cnt++)
			{
				if (access(inputFile[cnt].output, 0) == FALSE)
				{
					existNum++;
					printf("\n%d %s", existNum, inputFile[cnt].output);
				}
			}
			if (existNum > 0)
			{
				printf("\n存在以上 %d 个已经存在的文件，继续将会被覆盖"
					   "\n如列表不完整请设置更大的屏幕缓冲区大小"
					   "\n输入Y或y继续 其他任意字符退出\n请输入 ", existNum);
				fflush(stdin);
				char ch = getchar();
				fflush(stdin);
				if (ch != 'Y' && ch != 'y')
				{
					free(inputFile);
					inputFile = NULL;
					goto MAINPAGE;
				}
			}
			
			printf("\n> 任务正在开始 共 %d 个文件", i);
			for (cnt = 0; cnt < i; cnt++)
			{
				char code[4] = "000";
				DANMAKU *danmakuPoorHead = NULL;
				clock_t startTime, endTime;
				
				printf("\n> %d/%d 开始转换 ", cnt + 1, i);
				startTime = clock();
				
				/*读取*/
				code[0] += readXml(inputFile[cnt].input, &danmakuPoorHead, "n", inputFile[cnt].timeShift);
				/*编码转换*/
				if (inputFile[cnt].outputEncoding == UTF_8 && isUtf8(inputFile[cnt].fontName) == FALSE)
				{/*对字体说明文本*/
					transcoding(ANSI, UTF_8, inputFile[cnt].fontName, NULL, 0);
				}
				else if (inputFile[cnt].outputEncoding == ANSI && isUtf8(inputFile[cnt].fontName) == TRUE)
				{
					transcoding(UTF_8, ANSI, inputFile[cnt].fontName, NULL, 0);
				}
				transListCoding(danmakuPoorHead, inputFile[cnt].outputEncoding);/*对全部弹幕*/ 
				/*排序*/
				code[1] += sortList(&danmakuPoorHead);
				/*写出*/
				code[2] += writeAss(inputFile[cnt].output,/*输出文件*/
								    danmakuPoorHead,/*头指针*/
								    inputFile[cnt].resX,/*分辨率宽*/
								    inputFile[cnt].resY,/*分辨率高*/
								    inputFile[cnt].fontSize,/*字号*/
								    inputFile[cnt].fontName,/*字体(utf-8)*/
								    inputFile[cnt].shadow,/*阴影(0-4)*/
								    inputFile[cnt].outline,/*描边(0-4)*/
								    inputFile[cnt].rollTime,/*滚动速度（滚动弹幕）*/
								    inputFile[cnt].holdTime,/*停留时间（现隐弹幕）*/ 
								    inputFile[cnt].density,/*密度*/
								    inputFile[cnt].opacity,/*不透明度*/
								    inputFile[cnt].blank, /*下部留空*/
								    inputFile[cnt].blockMode,/*屏蔽*/
								    inputFile[cnt].debugMode);/*调试模式*/
				endTime = clock();
				
				freeList(danmakuPoorHead);
				if (strcmp(code ,"000") == 0 || strcmp(code ,"009") == 0)
				{
					printf(" -> 转换成功");
					printf(" 耗时 %d ms 状态编码 C%s", endTime - startTime, code);
					printf("\n  输出文件 %s", inputFile[cnt].output);
				}
				else
				{
					failNum++;
					printf(" -> 转换失败 ");
					printf(" 耗时 %d ms 状态编码 C%s ", endTime - startTime, code);
					printErrInfo(code);/*解释编码*/
				}
				endTime = clock();
			}
			
			free(inputFile);
			inputFile = NULL;
			printf("\n--------------------------------");
			printf("\n转换结束 %d 个成功，%d个失败", i - failNum, failNum);
			printf("\nMade by TIKM");
			printf("\nhttps://github.com/HITIKM/DanmakuFactory\n");
			system("pause");
		}
		else if (firSelected == 1)
		{/*更新与帮助*/
			showCursor(FALSE);/*隐藏指针*/
			system("cls");
			secSelected = 1;
			key = 0;
			do {
				setPos(0, 0);
				printf("DanmakuFactory v%s\n", VERSION);
				printf("--------------------------------");
				printMenuText(0, 2, secSelected, "> ", 0x0F, 0xF0, FALSE, 10,
							  "> 获取更新", 
							  "  github https://github.com/HITIKM/DanmakuFactory/tree/master/release",
			                  "  百度网盘 https://pan.baidu.com/s/1mkMaiq8AaUFUAGmv0s74vw 提取码：5vqj",
							  "> 教程",
							  "  官网 http://tikm.org/df/help/",
							  "> 反馈",
							  "  邮箱 hkm@tikm.org",
							  "  github https://github.com/HITIKM/DanmakuFactory/issues",
							  "  官网 https://df.tikm.org/fk/ (如果做好了的话)",
							  "> 返回");
				printf("\n--------------------------------");
				printf("\n↑↓选择  ENTER 跳转到对应网页");
				fflush(stdin);
				key = getch();
				fflush(stdin);
				
				if (key == UP)
				{
					if (secSelected == 0)
					{
						secSelected = 9;
					}
					else
					{
						secSelected--;
					}
				}
				else if (key == DOWN)
				{
					if (secSelected == 9)
					{
						secSelected = 0;
					}
					else
					{
						secSelected++;
					}
				}
				else if (key == ENTER && secSelected != 9)
				{
					switch (secSelected)
					{
						case 1:
						{
							system("start https://github.com/HITIKM/DanmakuFactory/tree/master/release");
							break;
						}
						case 2:
						{
							system("start https://pan.baidu.com/s/1mkMaiq8AaUFUAGmv0s74vw");
							break;
						}
						case 4:
						{
							system("start http://tikm.org/df/help/");
							break;
						}
						case 6:
						{
							system("start mailto:hkm@tikm.org");
							break;
						}
						case 7:
						{
							system("start https://github.com/HITIKM/DanmakuFactory/issues");
							break;
						}
					}
				}
				else if (key == ENTER && secSelected == 9)
				{
					break;
				}
			} while (TRUE);
			
			showCursor(TRUE);/*显示指针*/ 
		}
		else if (firSelected == 2)
		{/*退出*/ 
			exit(0); 
		}
		goto MAINPAGE;
	}
	else
	{
		/*命令行调用
		./danmakuFactory [-h][-s][-ip 输入文件名][-if 输入文件格式][-op 输出文件名]
					[-of 输出文件格式][-t 时轴偏移][-rx 分辨率宽][-ry 分辨率高][-rt 滚动弹幕滚动时间]
					[-ht 固定弹幕存活时间][-d 弹幕密度][-fs 文字大小][-fn 字体][-o 不透明度][-l 描边]
					[-s 阴影][-b 底部留白][-bm 屏蔽模式][-dm 调试模式]*/
		BOOL save = FALSE;
		float timeShift = 0.00;
		char inputFormat[MAX_TEXT_LENGTH] = {0};
		char outputFormat[MAX_TEXT_LENGTH] = {0};
		char inputFileName[MAX_TEXT_LENGTH] = {0}, outputFileName[MAX_TEXT_LENGTH] = {0};
		printf("DanmakuFactory v%s\n", VERSION);
		for (cnt = 1; cnt < argc; cnt++)
		{
			if (argv[cnt][0] == '-')
			{/*将选项全部转换为小写以支持大小写混用*/
				toLower(NULL, argv[cnt]);
			}
			else
			{/*非选项直接跳过*/
				continue;
			}
			
			/*参数可选的选项*/
			if ((strcmp(argv[cnt], "-h") == 0 || strcmp(argv[cnt], "--help") == 0) && argc == 2)
			{/*帮助*/
				printf("\n> 命令行调用_帮助");
				printf("\n  ./danmakuFactory [-h][-s][-ip 输入文件名][-if 输入文件格式][-op 输出文件名]"
							"[-of 输出文件格式][-oe 输出文件编码][-t 时轴偏移][-rx 分辨率宽][-ry 分辨率高]"
							"[-rt 滚动弹幕滚动时间][-ht 固定弹幕存活时间][-d 弹幕密度]"
							"[-fs 文字大小][-fn 字体][-o 不透明度][-l 描边][-sd 阴影]"
							"[-b 底部留白][-bm 屏蔽模式][-dm 调试模式]"

					   "\n\n> 选项解释"
					   "\n  -h, --help 显示帮助文本，除非存在其他选项"
					   "\n  -s, --set 将设置保存到文件，没有其他选项则将列出当前文件中的设置值；"
							   "转换时加入此选项表示将本次设置保存到文件中；如果输入文件名-ip缺省则"
							   "只修改设置而不进行其他操作"
					
					   "\n\n  -ip, --input 输入文件名，除非使用了-s选项，否则缺省将导致出错"
					   "\n  -if, --inputformat 输入文件格式，缺省时程序将自动判断"
					   "\n  -op, --output 输出文件名，缺省时默认为 \"输入文件名.输出文件格式\""
					   "\n  -of, --outputformat 输出文件格式，缺省时默认为ass"
					   "\n  -oe, --outputencoding 输出文件编码，缺省时将使用配置文件中的值"
					   "\n  -t, --timeshift 时轴偏移量，缺省时默认为0.00"
					
					   "\n\n  -rx, --resx 分辨率宽，缺省时将使用配置文件中的值"
					   "\n  -ry, --resy 分辨率高，缺省时将使用配置文件中的值"
					   "\n  -rt, --rolltime 滚动弹幕滚动时间，缺省时将使用配置文件中的值"
					   "\n  -ht, --holdtime 固定弹幕存活时间，缺省时将使用配置文件中的值"
					   "\n  -d, --density 弹幕密度，缺省时将使用配置文件中的值"
					   "\n  -fs, --fontsize 文字大小，缺省时将使用配置文件中的值"
					   "\n  -fn, --fontname 字体名称，缺省时将使用配置文件中的值"
					   "\n  -o, --opacity 不透明度，缺省时将使用配置文件中的值"
					   "\n  -l, --outline 描边程度，缺省时将使用配置文件中的值"
					   "\n  -sd, --shadow 阴影程度，缺省时将使用配置文件中的值"
					   "\n  -b, --blank 底部留白，缺省时将使用配置文件中的值"
					   "\n  -bm, --blockmode 屏蔽模式，缺省时将使用配置文件中的值"
					   "\n  -dm, --debugmode 调试模式，缺省时将使用配置文件中的值"
					   "\n\n> 注意"
					   "\n  如果参数带有空格请使用双引号，否则将会截断。如：\"Microsoft YaHei\""
					   "\n  如果参数带有负号请使用括号，否则将解析为选项。如：(-1024.25)"
					   "\n\n> 举例"
					   "\n  danmakuFactory -ip \"D:/test.xml\"");
				exit(0); 
			}
			else if (strcmp(argv[cnt], "-s") == 0 || strcmp(argv[cnt], "--set") == 0)
			{/*设置*/
				if (argc == 2)
				{
					printf("\n> 设置项");
					printf("\n  %10s 分辨率宽 = %d", "resX", defaultConfig.resX);
					printf("\n  %10s 分辨率高 = %d", "resY", defaultConfig.resY);
					printf("\n");
					printf("\n  %10s 滚动弹幕速度（秒） = %d", "rollTime", defaultConfig.rollTime);
					printf("\n  %10s 固定弹幕存活时间（秒） = %d", "holdTime", defaultConfig.holdTime);
					printf("\n  %10s 弹幕密度（条） = %d", "density", defaultConfig.density);
					printf("\n");
					if (defaultConfig.outputEncoding == UTF_8)
					{
						printf("\n  %10s 输出编码 = utf-8", "outputEncoding");
					}
					else
					{
						printf("\n  %10s 输出编码 = ansi", "outputEncoding");
					}
					printf("\n  %10s 文字大小 = %d", "fontSize", defaultConfig.fontSize);
					
					
					if (isUtf8(defaultConfig.fontName) == TRUE)
					{/*对字体说明文本*/
						transcoding(UTF_8, ANSI, defaultConfig.fontName, NULL, 0);
					}
					printf("\n  %10s 字体 = %s", "fontName", defaultConfig.fontName);
					
					printf("\n  %10s 不透明度（0-255） = %d", "opacity", defaultConfig.opacity);
					printf("\n  %10s 描边（0-4） = %d", "outline", defaultConfig.outline);
					printf("\n  %10s 阴影（0-4） = %d", "shadow", defaultConfig.shadow);
					printf("\n");
					printf("\n  %10s 底部留白（像素） = %d", "blank", defaultConfig.blank);
					printf("\n  %10s 按类型屏蔽（右左/左右/顶部/底部/特殊/彩色/重复） = %s",
							"blockMode", defaultConfig.blockMode);
					printf("\n  %10s 调试模式（数据表格/分布图） = %s",
							"debugMode", defaultConfig.debugMode);
					printf("\n 上面两项 1 表示对应位置项开启，0 表示对应位置项关闭");
					exit(0);
				}
				save = TRUE;
				continue; 
			}
			
			/*参数必选的选项*/
			if (cnt + 1 < argc)
			{/*检查参数是否缺省*/ 
				if (argv[cnt + 1][0] == '-')
				{
					printf("> 错误：命令行无法识别或者不完整", argv[cnt]);
					printf("\n\n> 调用方法");
					printf("\n  ./danmakuFactory [-h][-s][-ip 输入文件名][-if 输入文件格式][-op 输出文件名]"
								"[-of 输出文件格式][-oe 输出文件编码][-t 时轴偏移][-rx 分辨率宽][-ry 分辨率高]"
								"[-rt 滚动弹幕滚动时间][-ht 固定弹幕存活时间][-d 弹幕密度]"
								"[-fs 文字大小][-fn 字体][-o 不透明度][-l 描边][-sd 阴影]"
								"[-b 底部留白][-bm 屏蔽模式][-dm 调试模式]");
					printf("\n\n ./danmakuFactory -h 查看详细");
					exit(1);
				}
			}
			else
			{
				printf("> 错误：命令行无法识别或者不完整", argv[cnt]);
				printf("\n\n> 调用方法");
				printf("\n  ./danmakuFactory [-h][-s][-ip 输入文件名][-if 输入文件格式][-op 输出文件名]"
							"[-of 输出文件格式][-oe 输出文件编码][-t 时轴偏移][-rx 分辨率宽][-ry 分辨率高]"
							"[-rt 滚动弹幕滚动时间][-ht 固定弹幕存活时间][-d 弹幕密度]"
							"[-fs 文字大小][-fn 字体][-o 不透明度][-l 描边][-sd 阴影]"
							"[-b 底部留白][-bm 屏蔽模式][-dm 调试模式]");
				printf("\n\n ./danmakuFactory -h 查看详细");
				exit(1);
			}
			
			if (strcmp(argv[cnt], "-ip") == 0 || strcmp(argv[cnt], "--input") == 0)
			{/*输入文件名*/
				strcpy(inputFileName, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-if") == 0 || strcmp(argv[cnt], "--inputformat") == 0)
			{/*输入文件格式*/
				strcpy(inputFormat, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-op") == 0 || strcmp(argv[cnt], "--output") == 0)
			{/*输出文件名*/
				strcpy(outputFileName, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-of") == 0 || strcmp(argv[cnt], "--outputformat") == 0)
			{/*输出文件格式*/
				strcpy(inputFormat, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-oe") == 0 || strcmp(argv[cnt], "--outputencoding") == 0)
			{/*输出文件编码*/
				if (strcmp(toLower(NULL, argv[cnt + 1]), "utf-8") == 0)
				{
					defaultConfig.outputEncoding = UTF_8;
				}
				else if (strcmp(toLower(NULL, argv[cnt + 1]), "ansi") == 0)
				{
					defaultConfig.outputEncoding = ANSI;
				}
				else
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        可选值目前只有utf-8与ansi");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-t") == 0 || strcmp(argv[cnt], "--timeshift") == 0)
			{/*时轴偏移*/
				if (!isDesignatedChar(argv[cnt + 1], "()-.0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，因为有非法字符", argv[cnt]);
					exit(1);
				}
				timeShift = strToFloat(argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-rx") == 0 || strcmp(argv[cnt], "--resx") == 0)
			{/*分辨率宽*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，分辨率宽必须是大于0的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.resX = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.resX <= 0)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        分辨率宽必须是大于0的整数");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-ry") == 0 || strcmp(argv[cnt], "--resy") == 0)
			{/*分辨率高*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，分辨率高必须是大于0的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.resY = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.resY <= 0)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        分辨率高必须是大于0的整数");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-rt") == 0 || strcmp(argv[cnt], "--rolltime") == 0)
			{/*滚动弹幕滚动速度*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，滚动弹幕滚动速度必须是大于0的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.rollTime = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.rollTime <= 0)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        滚动弹幕滚动速度必须是大于0的整数");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-ht") == 0 || strcmp(argv[cnt], "--holdtime") == 0)
			{/*固定弹幕存活时间*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，固定弹幕存活时间必须是大于0的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.holdTime = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.holdTime <= 0)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        固定弹幕存活时间必须是大于0的整数");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-d") == 0 || strcmp(argv[cnt], "--density") == 0)
			{/*弹幕密度*/
				if (!isDesignatedChar(argv[cnt + 1], "()-.0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，因为有非法字符", argv[cnt]);
					exit(1);
				}
				defaultConfig.density = strToFloat(argv[cnt + 1]);
				if (defaultConfig.density < -1)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        弹幕密度必须是大于或等于-1的整数");
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-fs") == 0 || strcmp(argv[cnt], "--fontsize") == 0)
			{/*文字大小*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，文字大小必须是大于0的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.fontSize = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.fontSize <= 0)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        文字大小必须是大于0的整数"); 
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-fn") == 0 || strcmp(argv[cnt], "--fontname") == 0)
			{/*字体名称*/
				strcpy(defaultConfig.fontName, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-o") == 0 || strcmp(argv[cnt], "--opacity") == 0)
			{/*不透明度*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，不透明度必须是0 - 255的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.opacity = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.opacity < 0 || defaultConfig.opacity > 255) 
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        不透明度必须是0 - 255的整数"); 
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-l") == 0 || strcmp(argv[cnt], "--outline") == 0)
			{/*不透明度*/
				if (!isDesignatedChar(argv[cnt + 1], "()01234"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，描边必须是0 - 4的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.outline = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.outline < 0 || defaultConfig.outline > 4)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        描边必须是0 - 4的整数"); 
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-sd") == 0 || strcmp(argv[cnt], "--shadow") == 0)
			{/*不透明度*/
				if (!isDesignatedChar(argv[cnt + 1], "()01234"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，阴影必须是0 - 4的整数", argv[cnt]);
					exit(1);
				}
				defaultConfig.shadow = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.shadow < 0 || defaultConfig.shadow > 4)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        阴影必须是0 - 4的整数"); 
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-b") == 0 || strcmp(argv[cnt], "--blank") == 0)
			{/*底部留白*/
				if (!isDesignatedChar(argv[cnt + 1], "()0123456789"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，分辨率高为%d时，底部留白必须是0 - %d的整数",
							argv[cnt], defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
				defaultConfig.shadow = (int)(strToFloat(argv[cnt + 1]));
				if (defaultConfig.shadow < 0 ||
					defaultConfig.shadow > defaultConfig.resY - defaultConfig.fontSize)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        分辨率高为%d时，底部留白必须是0 - %d的整数", 
							defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
			}
			else if (strcmp(argv[cnt], "-bm") == 0 || strcmp(argv[cnt], "--blockmode") == 0)
			{/*屏蔽模式*/
				if (!isDesignatedChar(argv[cnt + 1], "()01"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，屏蔽模式值只能为 0 或 1",
							argv[cnt], defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
				if (strlen(argv[cnt + 1]) != 7)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        参数只能由7个0或1组成",
							argv[cnt], defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
				strcpy(defaultConfig.blockMode, argv[cnt + 1]);
			}
			else if (strcmp(argv[cnt], "-dm") == 0 || strcmp(argv[cnt], "--debugmode") == 0)
			{/*调试模式*/
				if (!isDesignatedChar(argv[cnt + 1], "()01"))
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        程序无法接受值 %s ，调试模式值只能为 0 或 1",
							argv[cnt], defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
				if (strlen(argv[cnt + 1]) != 2)
				{
					printf("> 错误：选项%s的参数错误", argv[cnt]);
					printf("\n        参数只能由2个0或1组成",
							argv[cnt], defaultConfig.resY, defaultConfig.resY - defaultConfig.fontSize);
					exit(1);
				}
				strcpy(defaultConfig.debugMode, argv[cnt + 1]);
			}
			else
			{
				printf("> 错误：命令行无法识别或不完整");
				printf("\n        无法识别 %s", argv[cnt]);
				printf("\n\n> 调用方法");
				printf("\n  ./danmakuFactory [-h][-s][-ip 输入文件名][-if 输入文件格式][-op 输出文件名]"
							"[-of 输出文件格式][-oe 输出文件编码][-t 时轴偏移][-rx 分辨率宽][-ry 分辨率高]"
							"[-rt 滚动弹幕滚动时间][-ht 固定弹幕存活时间][-d 弹幕密度]"
							"[-fs 文字大小][-fn 字体][-o 不透明度][-l 描边][-sd 阴影]"
							"[-b 底部留白][-bm 屏蔽模式][-dm 调试模式]");
				printf("\n\n ./danmakuFactory -h 查看详细");
				exit(1);
			}
		}
		
		/*写配置文件*/
		if (save == TRUE)
		{
			if (!writeConfigFile(defaultConfig, configFilePath))
			{
				printf("\n> 警告：设置无法更新到文件，因为配置文件丢失或不可写\n");
			}
		}
		
		if (inputFileName[0] == '\0')
		{
			exit(0);
		} 
		
		/*转换 xml 转 ass*/
		if (outputFileName[0] == '\0')
		{
			sprintf(outputFileName, "%s.ass", inputFileName);
		}
		
		if(!access(outputFileName, 0))
		{
			printf("\n输出文件%s已存在，继续执行原文件将会被覆盖\n", outputFileName);
			printf("输入y或Y继续，其他任意字符退出\n");
			fflush(stdin);
			char ch = getchar();
			if(ch != 'Y' && ch != 'y')
			{
				exit(0);
			}
		}
		
		int rt = 0;
		char code[] = "000";
		DANMAKU *danmakuPoorHead = NULL;
		clock_t startTime, endTime;
		
		printf("\n> 转换开始");
		startTime = clock();
		
		
		code[0] += readXml(inputFileName, &danmakuPoorHead, "n", timeShift);
		
		/*编码转换*/ 
		if (defaultConfig.outputEncoding == UTF_8 && isUtf8(defaultConfig.fontName) == FALSE)
		{/*对字体说明文本*/
			transcoding(ANSI, UTF_8, defaultConfig.fontName, NULL, 0);
		}
		else if (defaultConfig.outputEncoding == ANSI && isUtf8(defaultConfig.fontName) == TRUE)
		{
			transcoding(UTF_8, ANSI, defaultConfig.fontName, NULL, 0);
		}
		transListCoding(danmakuPoorHead, defaultConfig.outputEncoding);/*对全部弹幕*/
		
		code[1] += sortList(&danmakuPoorHead);
		code[2] += writeAss(outputFileName,/*输出文件*/
						    danmakuPoorHead,/*头指针*/
						    defaultConfig.resX, defaultConfig.resY,/*分辨率宽/分辨率高*/
						    defaultConfig.fontSize, defaultConfig.fontName,/*字号/字体(utf-8)*/
						    defaultConfig.shadow, defaultConfig.outline,/*阴影(0-4)/描边(0-4)*/
						    defaultConfig.rollTime, defaultConfig.holdTime,/*滚动速度（滚动弹幕）/停留时间（现隐弹幕）*/ 
						    defaultConfig.density, defaultConfig.opacity,/*密度/不透明度*/
						    defaultConfig.blank, /*下部留空*/
						    defaultConfig.blockMode,/*屏蔽（右左/左右/顶部/底部/特殊/彩色/重复）*/
						    defaultConfig.debugMode);/*调试模式（数据统计/分布图）*/
		endTime = clock();
		
		if (strcmp(code, "000") == 0 || strcmp(code, "009") == 0)
		{
			printf("-> 转换成功");
			printf(" 耗时 %d ms 状态编码 C%s", endTime - startTime, code);
		}
		else
		{
			printf("-> 转换失败");
			printf(" 耗时 %d ms 状态编码 C%s ", endTime - startTime, code);
			printErrInfo(code);
		}
		
		
		printf("\n输出文件为 %s", outputFileName);
		printf("\nMade by TIKM");
		printf("\nhttps://github.com/HITIKM/DanmakuFactory");
		endTime = clock();
		exit(0);
	}
	return 0;
}

/*
读配置文件
参数：
配置信息结构体指针/配置文件名/
*/ 
void readConfigFile(CONFIG *config, char *fileName)
{
	BOOL noErr = TRUE;
	char tempText[MAX_TEXT_LENGTH];
	
	(*config).resX = GetPrivateProfileInt("DanmakuSet", "resX", 1920, fileName);
	(*config).resY = GetPrivateProfileInt("DanmakuSet", "resY", 1080, fileName);
	(*config).fontSize = GetPrivateProfileInt("DanmakuSet", "fontSize", 38, fileName);
	(*config).shadow = GetPrivateProfileInt("DanmakuSet", "shadow", 1, fileName);
	(*config).outline = GetPrivateProfileInt("DanmakuSet", "outline", 0, fileName);
	(*config).rollTime = GetPrivateProfileInt("DanmakuSet", "rollTime", 10, fileName);
	(*config).holdTime = GetPrivateProfileInt("DanmakuSet", "holdTime", 10, fileName);
	(*config).density = GetPrivateProfileInt("DanmakuSet", "density", 0, fileName);
	(*config).opacity = GetPrivateProfileInt("DanmakuSet", "opacity", 180, fileName);
	(*config).blank = GetPrivateProfileInt("DanmakuSet", "blank", 0, fileName);
	GetPrivateProfileString("DanmakuSet", "fontName", "Microsoft YaHei Light", (*config).fontName,
							MAX_TEXT_LENGTH, fileName);
	 GetPrivateProfileString("DanmakuSet", "opEncoding", "UTF-8", tempText, MAX_TEXT_LENGTH, fileName);					
	if (strcmp(toLower(NULL, tempText), "utf-8") == 0)
	{
		(*config).outputEncoding = UTF_8;
	}
	else
	{
		(*config).outputEncoding = ANSI;
	}
	
	GetPrivateProfileString("DanmakuSet", "blockR2L", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[0] = '1';
	}
	else
	{
		(*config).blockMode[0] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockL2R", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[1] = '1';
	}
	else
	{
		(*config).blockMode[1] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockTop", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[2] = '1';
	}
	else
	{
		(*config).blockMode[2] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockBottom", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[3] = '1';
	}
	else
	{
		(*config).blockMode[3] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockSpecial", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[4] = '1';
	}
	else
	{
		(*config).blockMode[4] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockColor", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[5] = '1';
	}
	else
	{
		(*config).blockMode[5] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "blockRepeat", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).blockMode[6] = '1';
	}
	else
	{
		(*config).blockMode[6] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "debugTable", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).debugMode[0] = '1';
	}
	else
	{
		(*config).debugMode[0] = '0';
	}
	
	GetPrivateProfileString("DanmakuSet", "debugChart", "false", tempText, MAX_TEXT_LENGTH, fileName);
	if (strcmp(toLower(NULL, tempText), "true") == 0)
	{
		(*config).debugMode[1] = '1';
	}
	else
	{
		(*config).debugMode[1] = '0';
	}
}

/*
写配置文件
参数：
配置信息结构体/配置文件名/
成功返回TRUE 失败返回FALSE
*/ 
BOOL writeConfigFile(CONFIG config, char *fileName)
{
	BOOL noErr = TRUE;
	char tempText[MAX_TEXT_LENGTH];
	
	sprintf(tempText, "%d", config.resX);
	noErr &= WritePrivateProfileString("DanmakuSet", "resX", tempText, fileName);
	
	sprintf(tempText, "%d", config.resY);
	noErr &= WritePrivateProfileString("DanmakuSet", "resY", tempText, fileName);
	
	sprintf(tempText, "%d", config.rollTime);
	noErr &= WritePrivateProfileString("DanmakuSet", "RollTime", tempText, fileName);
	
	sprintf(tempText, "%d", config.holdTime);
	noErr &= WritePrivateProfileString("DanmakuSet", "holdTime", tempText, fileName);
	
	sprintf(tempText, "%d", config.shadow);
	noErr &= WritePrivateProfileString("DanmakuSet", "shadow", tempText, fileName);
	
	sprintf(tempText, "%d", config.outline);
	noErr &= WritePrivateProfileString("DanmakuSet", "outline", tempText, fileName);
	
	sprintf(tempText, "%d", config.density);
	noErr &= WritePrivateProfileString("DanmakuSet", "density", tempText, fileName);
	
	sprintf(tempText, "%d", config.opacity);
	noErr &= WritePrivateProfileString("DanmakuSet", "opacity", tempText, fileName);
	
	sprintf(tempText, "%d", config.blank);
	noErr &= WritePrivateProfileString("DanmakuSet", "blank", tempText, fileName);
	
	sprintf(tempText, "%d", config.fontSize);
	noErr &= WritePrivateProfileString("DanmakuSet", "fontSize", tempText, fileName);
	
	noErr &= WritePrivateProfileString("DanmakuSet", "fontName", config.fontName, fileName);
	
	if (config.blockMode[0] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockR2L", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockR2L", "false", fileName);
	}
	
	if (config.blockMode[1] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockL2R", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockL2R", "false", fileName);
	}
	
	if (config.blockMode[2] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockTop", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockTop", "false", fileName);
	}
	
	if (config.blockMode[3] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockBottom", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockBottom", "false", fileName);
	}
	
	if (config.blockMode[4] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockSpecial", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockSpecial", "false", fileName);
	}
	
	if (config.blockMode[5] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockColor", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockColor", "false", fileName);
	}
	
	if (config.blockMode[6] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockRepeat", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "blockRepeat", "false", fileName);
	}
	
	if (config.debugMode[0] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "debugTable", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "debugTable", "false", fileName);
	}
	
	if (config.debugMode[1] != '0')
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "debugChart", "true", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "debugChart", "false", fileName);
	}
	
	if (config.outputEncoding != UTF_8)
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "opEncoding", "ansi", fileName);
	}
	else
	{
		noErr &= WritePrivateProfileString("DanmakuSet", "opEncoding", "utf-8", fileName);
	}
	
	return noErr;
}

/*
打印转换错误原因 
参数：
状态码 
*/
void printErrInfo(char *code)
{
	if (strcmp(code, "000") == 0 || strcmp(code, "009") == 0)
	{
		printf("正常");
	}
	else if (code[0] == '1')
	{
		printf("打开文件失败");
	}
	else if (code[0] == '2' || code[0] == '3' || code[0] == '4')
	{
		printf("读文件时发生错误");
	}
	else if (code[0] == '5' || code[0] == '6' || code[1] == '2' || (code[2] >= '3' && code[2] <= '7'))
	{
		printf("内存操作发生错误");
	}
	else if (code[0] == '7')
	{
		printf("文件未能按正确格式读入");
	}
	else if (code[2] == '2')
	{
		printf("创建或覆盖文件失败");
	}
	else if (code[2] == '8')
	{
		printf("写文件时发生错误");
	}
}
