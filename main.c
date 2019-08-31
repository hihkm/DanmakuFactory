#include "DanmakuFactory.h"
#include "ReadFile.c"
#include "WriteFile.c"
#include "ListProcessing.c"

#include <io.h>

typedef struct Config
{
	float timeShift;
	int resX, resY, fontSize, shadow, outline, speed, holdTime, density, opacity, blank;
	char fontName[MAX_TEXT_LENGTH], shieldMode[8], debugMode[3];
} CONFIG;

void PrintFunctionDebugData(char *name, long wasteTime, int returnValue);
char *timestampToText(time_t timestamp, char *text); 

int main(void)
{
	char tempText[MAX_TEXT_LENGTH];
	char inputFileName[MAX_TEXT_LENGTH], outputFileName[MAX_TEXT_LENGTH];
	/*文件导入页*/ 
	printf("DanmakuFactory v%s\n", VERSION);
	printf("------------------------\n");
	/*填写输入输出文件路径*/
	while(TRUE)
	{
		fflush(stdin);
		printf("输入文件名 ");
		fgets(inputFileName, MAX_TEXT_LENGTH / 2, stdin);
		if(inputFileName[strlen(inputFileName + 1)] == '\n')
		{
			inputFileName[strlen(inputFileName + 1)] = '\0';
		}
		DeQuotMarks(inputFileName);/*如果有的话 去两端引号*/
		if(access(inputFileName, 0))
		{
			printf("文件 %s 不存在，请重新输入\n", inputFileName); 
		}
		else
		{
			break;
		}
	}
	
	strcpy(outputFileName, inputFileName);
	strcat(outputFileName, ".ass");
	fflush(stdin);
	
	
	if(!access(outputFileName, 0))
	{
		printf("\n输出文件%s已存在，继续执行原文件将会被覆盖\n", outputFileName);
		printf("输入y或Y继续，其他任意字符退出\n");
		char ch = getchar();
		if(ch != 'Y' && ch != 'y')
		{
			exit(0);
		}
	}
	
	
	/*读取配置文件*/
	FILE *configFile;
	CONFIG danmakuConfig;
	if((configFile = fopen("DanmakuFactoryConfig.bin", "rb")) == NULL)
	{
		danmakuConfig.resX = 1920;
		danmakuConfig.resY = 1080;
		
		danmakuConfig.speed = 10;
		danmakuConfig.holdTime = 5;
		danmakuConfig.density = 0;
		
		danmakuConfig.opacity = 180;
		danmakuConfig.outline = 0;
		danmakuConfig.shadow = 0;
		strcpy(danmakuConfig.fontName, "Microsoft YaHei Light");
		
		danmakuConfig.timeShift = 0.00;
		danmakuConfig.blank = 0; 
		strcpy(danmakuConfig.shieldMode, "0000000");
		strcpy(danmakuConfig.debugMode, "00");
		danmakuConfig.fontSize = 38;
	}
	else
	{
		fread(&danmakuConfig, sizeof(CONFIG), 1, configFile);
		fclose(configFile);
		configFile = NULL;
	}
	
	/*弹幕设置页*/
	while(TRUE)
	{
		system("cls");
		printf("DanmakuFactory v%s\n", VERSION);
		printf("%s\n\n", inputFileName);
		printf("弹幕设置\n");
		printf("------------------------");
		printf("\n 1 分辨率宽 = %d", danmakuConfig.resX);
		printf("\n 2 分辨率高 = %d", danmakuConfig.resY);
		
		printf("\n\n 3 滚动弹幕速度（秒） = %d", danmakuConfig.speed);
		printf("\n 4 固定弹幕速度（秒） = %d", danmakuConfig.holdTime);
		printf("\n 5 弹幕密度（条） = %d", danmakuConfig.density);
		
		printf("\n\n 6 文字大小 = %d", danmakuConfig.fontSize);
		printf("\n 7 字体 = %s", danmakuConfig.fontName);
		printf("\n 8 不透明度（0-255） = %d", danmakuConfig.opacity);
		printf("\n 9 描边（0-4） = %d", danmakuConfig.outline);
		printf("\n a 阴影（0-4） = %d", danmakuConfig.shadow);
		
		printf("\n\n b 时轴偏移（浮点数） = %f", danmakuConfig.timeShift);
		printf("\n c 下方留白（像素） = %d", danmakuConfig.blank);
		printf("\n d 按类型屏蔽（右左/左右/顶部/底部/特殊/彩色/重复） = %s", danmakuConfig.shieldMode);
		printf("\n e 调试模式（数据表格/分布图） = %s", danmakuConfig.debugMode);
		printf("\n\n上面两项 1 表示对应位置项开启，0 表示对应位置项关闭");
		
		printf("\n------------------------\n"); 
		printf("请输入要修改的项目前面的序号\n输入0开始转换\n");
		printf("请输入 ");
		fflush(stdin);
		char ch = getchar();
		
		fflush(stdin);
		system("cls");
		printf("DanmakuFactory v1.10\n");
		printf("%s\n\n", inputFileName);
		printf("弹幕设置\n");
		printf("------------------------\n");
		switch(ch)
		{
			case '0':
			{
				goto SETEND;
				break;
			}
			case '1':
			{
				do{
					printf("请输入一个大于0的整数\n");
					printf("请输入分辨率宽 ");
					scanf("%d", &danmakuConfig.resX);
				}while(danmakuConfig.resX <= 0);
				break;
			}
			case '2':
			{
				do{
					printf("请输入一个大于0的整数\n");
					printf("请输入分辨率高 ");
					scanf("%d", &danmakuConfig.resY);
				}while(danmakuConfig.resY <= 0);
				break;
			}
			case '3':
			{
				do{
					printf("请输入一个大于0的整数\n");
					printf("滚动弹幕速度（秒） ");
					scanf("%d", &danmakuConfig.speed);
				}while(danmakuConfig.speed <= 0);
				break;
			}
			case '4': 
			{
				do{
					printf("请输入一个大于0的整数\n");
					printf("固定弹幕速度（秒） ");
					scanf("%d", &danmakuConfig.holdTime);
				}while(danmakuConfig.holdTime <= 0);
				break;
			}
			case '5':
			{
				do{
					printf("0 表示无限制，-1 表示不重叠\n");
					printf("请输入一个大于或等于-1的整数\n");
					printf("弹幕密度（条） ");
					scanf("%d", &danmakuConfig.density);
				}while(danmakuConfig.density < -1);
				break;
			}
			case '6':
			{
				do{
					printf("请输入一个大于0的整数\n");
					printf("文字大小 ");
					scanf("%d", &danmakuConfig.fontSize);
				}while(danmakuConfig.fontSize <= 0);
				break;
			}
			case '7':
			{
				printf("因编码问题输入中文可能会导致乱码\n");
				printf("字体 ");
				fgets(danmakuConfig.fontName, MAX_TEXT_LENGTH, stdin);
				if(danmakuConfig.fontName[strlen(danmakuConfig.fontName + 1)] == '\n')
				{
					danmakuConfig.fontName[strlen(danmakuConfig.fontName + 1)] = '\0';
				}
				break;
			}
			case '8':
			{
				do{
					printf("请输入一个0 - 255的整数\n");
					printf("不透明度 ");
					scanf("%d", &danmakuConfig.opacity);
				}while(danmakuConfig.opacity < 0 || danmakuConfig.opacity > 255);
				break;
			}
			case '9':
			{
				do{
					printf("请输入一个0 - 4的整数\n");
					printf("描边");
					scanf("%d", &danmakuConfig.outline);
				}while(danmakuConfig.outline < 0 || danmakuConfig.outline > 4);
				break;
			}
			case 'A':
			case 'a':
			{
				do{
					printf("请输入一个0 - 4的整数\n");
					printf("阴影 ");
					scanf("%d", &danmakuConfig.shadow);
				}while(danmakuConfig.shadow < 0 || danmakuConfig.shadow > 4);
				break;
			}
			case 'B':
			case 'b':
			{
				do{
					printf("请输入一个小数\n");
					printf("时轴偏移 ");
				}while(!scanf("%f", &danmakuConfig.timeShift));
				break;
			}
			case 'C':
			case 'c':
			{
				do{
					printf("请输入一个大于等于0的整数，0为不留白\n");
					printf("下方留白（像素） ");
					scanf("%d", &danmakuConfig.blank);
				}while(danmakuConfig.blank < 0);
				break;
			}
			case 'D':
			case 'd':
			{
				printf("顺序与括号中的相同 0 表示关闭，1 表示开启\n");
				printf("按类型屏蔽（右左/左右/顶部/底部/特殊/彩色/重复） ");
				fgets(danmakuConfig.shieldMode, 8, stdin);
				break;
			}
			case 'E':
			case 'e':
			{
				printf("顺序与括号中的相同 0 表示关闭，1 表示开启\n");
				printf("调试模式（数据表格/分布图） ");
				fgets(danmakuConfig.debugMode, 3, stdin);
				break;
			}
		}
		fflush(stdin); 
	}
	SETEND:;
	
	/*写配置文件*/
	if((configFile = fopen("DanmakuFactoryConfig.bin", "wb")) != NULL)
	{
		fwrite(&danmakuConfig, sizeof(CONFIG), 1, configFile);
		fclose(configFile);
	}
	
	/*开始转换*/
	system("cls");
	printf("DanmakuFactory v%s\n", VERSION);
	printf("%s\n", inputFileName);
	printf("------------------------");
	int rt;
	printf("\n%s [信息] 转换开始", timestampToText(time(NULL), tempText));
	DANMAKU *danmakuPoorHead = NULL;
	clock_t startTime, midTime, endTime;
	midTime = startTime = clock();
	
	
	/*读入文件*/
	printf("\n%s [信息] 开始读入文件", timestampToText(time(NULL), tempText));
	rt = ReadXml(inputFileName, &danmakuPoorHead, "n", danmakuConfig.timeShift);
	endTime = clock();
	PrintFunctionDebugData("ReadXml", endTime - midTime, rt);
	
	/*对弹幕池按时间进行桶排序*/
	printf("\n%s [信息] 开始排序弹幕", timestampToText(time(NULL), tempText));
	midTime = clock();
	rt = SortList(&danmakuPoorHead);
	endTime = clock();
	PrintFunctionDebugData("SortList", endTime - midTime, rt);
	
	
	/*写ass*/
	printf("\n%s [信息] 开始写入文件", timestampToText(time(NULL), tempText));
	midTime = clock();
	rt = WriteAss(outputFileName,/*输出文件*/
				  danmakuPoorHead,/*头指针*/
				  danmakuConfig.resX, danmakuConfig.resY,/*分辨率宽/分辨率高*/
				  danmakuConfig.fontSize, danmakuConfig.fontName,/*字号/字体(utf-8)*/
				  danmakuConfig.shadow, danmakuConfig.outline,/*阴影(0-4)/描边(0-4)*/
				  danmakuConfig.speed, danmakuConfig.holdTime,/*滚动速度（滚动弹幕）/停留时间（现隐弹幕）*/ 
				  danmakuConfig.density, danmakuConfig.opacity,/*密度/不透明度*/
				  danmakuConfig.blank, /*下部留空*/
				  danmakuConfig.shieldMode,/*屏蔽（右左/左右/顶部/底部/特殊/彩色/重复）*/
				  NULL);/*调试模式（数据统计/分布图）*/
	endTime = clock();
	PrintFunctionDebugData("WriteAss", endTime - midTime, rt);
	
	
	/*调试模式 这里单独调用写调试模式数据的函数只是为了方便调试，建议直接在写ass函数参数上补充模式即可*/
	midTime = clock();
	rt = WriteAssDebugPath(outputFileName, danmakuPoorHead, danmakuConfig.debugMode,
						   danmakuConfig.speed, danmakuConfig.holdTime, danmakuConfig.shieldMode);
	endTime = clock();
	PrintFunctionDebugData("WriteAssDebugPath", endTime - midTime, rt);
	
	printf("\n%s [信息] 转换完成", timestampToText(time(NULL), tempText));
	printf("\n\n转换完成不等价于转换成功，请查看上面日志是否有错误信息\n输出文件为 %s.ass\n\n", inputFileName);
	printf("\nMade by TIKM\n");
	printf("https://github.com/HITIKM/DanmakuFactory\n");
	endTime = clock();
	system("pause");
	return 0;
}

void PrintFunctionDebugData(char *name, long wasteTime, int returnValue)
{
	char tempText[MAX_TEXT_LENGTH]; 
	printf("\n%s [信息] 函数%s耗时", timestampToText(time(NULL), tempText), name);
	if(wasteTime > 1000)
	{
		printf(" %ld %03ld ms ", wasteTime / 1000, wasteTime % 1000);
	}
	else
	{
		printf(" %ld ms ", wasteTime);
	}
	printf("返回值为 %d", returnValue);
	return;
}

/*
时间戳转时间字符串 
参数：时间戳、用于放置返回字符串的字符数组】
返回值：传入数组的地址 
*/
char *timestampToText(time_t timestamp, char *text)
{
	char *ptr = text;
	int cnt;
	int hour, min, sec;
	
	/*将时间戳变成以北京时间为基准的*/
	timestamp += 8 * 3600;/*北京时间是东八区要在0时区基础上加8个小时*/
	
	/*计算时分秒*/
	sec = timestamp % 60;
	min = timestamp % 3600 / 60;
	hour = timestamp % (24 * 3600) / 3600;
	
	/*时*/
	text[0] = hour / 10 + '0';
	text[1] = hour % 10 + '0';
	/*分*/
	text[3] = min / 10 + '0';
	text[4] = min % 10 + '0';
	/*秒*/
	text[6] = sec / 10 + '0';
	text[7] = sec % 10 + '0';
	
	/*写分隔符号*/
	text[2] = text[5] = ':';
	text[8] = '\0';
	return text;
}
