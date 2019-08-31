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

#ifndef __DANMAKU_FACTORY_H__
#define __DANMAKU_FACTORY_H__

#include <windows.h>
#include <conio.h>
#include <assert.h>
#include <time.h>
#include <io.h>
#include <direct.h> 
#include <stdarg.h>

#define VERSION "1.31 release"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

#define MAX_TEXT_LENGTH 1024

/*初版配置 用于读取旧配置文件*/
typedef struct OldConfig
{
	float timeShift;
	int resX, resY, fontSize, shadow, outline, rollTime, holdTime, density, opacity, blank;
	char fontName[MAX_TEXT_LENGTH];
	char blockMode[8];
	char debugMode[3];
} OLDCONFIG;

/*1.30版本配置*/ 
typedef struct taskConfig
{
	/*不写入配置文件部分*/
	char input[MAX_TEXT_LENGTH];
//	char inputFormat[MAX_TEXT_LENGTH];
	char output[MAX_TEXT_LENGTH];
//	char outputFormat[MAX_TEXT_LENGTH];
	float timeShift;
	
	/*写入配置文件部分*/ 
//	UINT inputEncoding;/*输入文件编码*/
	UINT outputEncoding;/*输出文件编码*/ 
	int resX, resY, fontSize, shadow, outline, rollTime, holdTime, density, opacity, blank;
	char fontName[MAX_TEXT_LENGTH];
	char blockMode[8];
	char debugMode[3];
} CONFIG;

/*main.c*/
void readConfigFile(CONFIG *config, char *fileName);/*读配置文件*/
BOOL writeConfigFile(CONFIG config, char *fileName);/*写配置文件*/
void printErrInfo(char *code);/*打印错误信息*/ 

/*ui.c*/
void showCursor(BOOL show);/*显示或隐藏光标*/
void setPos(int x, int y);/*移动指针*/
int stylePrintf(WORD gobalStyle, WORD printStyle, char *format, ...);/*自定义配色的格式输出*/
void printMenuText(int x, int y, int selected, char *pointer,
				   WORD gobalStyle, WORD selectedStyle, BOOL allLineSetStyle,
				   int numOfLines, ...);/*打印菜单文字*/
int inputInt(int rangeLeft, int rangeRight, char *msgFormat, ...);/*引导用户输入一个特定范围的整数*/ 
 
#endif
