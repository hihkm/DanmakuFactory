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

#ifndef __DANMAKU_CONVERT_H__
#define __DANMAKU_CONVERT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_OF_TYPE 5
#define FLOAT_EPS 1e-4 
#define TIME_EPS 1e-4
#define MAX_TEXT_LENGTH 1024

#define TRUE 1
#define FALSE 0

#define ANSI CP_ACP
#define UTF_8 CP_UTF8

#define PRINT_ERR FALSE

#define IS_R2L(ptr) (ptr -> type == 1 || ptr -> type == -1)
#define IS_L2R(ptr) (ptr -> type == 2 || ptr -> type == -2)
#define IS_TOP(ptr) (ptr -> type == 3 || ptr -> type == -3)
#define IS_BTM(ptr) (ptr -> type == 4 || ptr -> type == -4)
#define IS_SPECIAL(ptr) (ptr -> type == 5 || ptr -> type == -5)
#define IS_NORMAL(ptr) (IS_R2L(ptr) || IS_L2R(ptr) || IS_TOP(ptr) || IS_BTM(ptr) || IS_SPECIAL(ptr))

typedef int BOOL;

typedef struct Danmaku
{
	float time;
	short type;
	short fontSize;
	int color;
	char *text;
	struct Danmaku *next;
} DANMAKU;

/*ReadFile.c*/
int readXml(const char *ipFile, DANMAKU **head, const char *mode, const float timeShift);/*读取xml文件加入弹幕池*/
void static errorExit(FILE *ipF, DANMAKU *head, DANMAKU *ptr);/*出错后程序退出前的处理*/

/*WriteFile.c*/
int writeAss(const char *opFileName, DANMAKU *head, const int resX, int resY, const int fontSize,
			 char *fontName,const int shadow, const int outline, const float rollTime, const float holdTime, 
			 const int density, const int opacity, const int blank,
			 char *blockMode, char *debugMode);/*将弹幕池写到ass文件*/
int writeAssDebugPath(const char *opFileName, DANMAKU *head, char *mode, const int rollTime, const int holdTime,
					  char *blockMode);/*写ass字幕的debug部分*/
float static getEndTime(DANMAKU *danmakuPtr, const int rollTime, const int holdTime);/*获取弹幕结束时间*/
int static printTime(FILE *filePtr, float time, char *endText);/*以ass格式标准打印时间*/
char static *toHexColor(int decColor, char *hexColor);/*转换十进制rgb颜色为十六进制颜色*/
char static *toHexOpacity(int decOpacity, char *hexOpacity);/*十进制透明度转十六进制透明度*/
int static findMin(float *array, const int numOfLine, const int stopSubScript, const int mode);/*寻找最小值*/
int static drawRectangle(FILE *opF, int startX, int startY, int width, int height);/*根据信息打印一个ass矩形*/
int static printDebugDataInt(FILE *filePtr, const float startTime, const float endTime, const int posX,
								const int posY, char *effect, const int data);/*根据信息打印debug数据表上的信息*/
int static printDebugDataStr(FILE *filePtr, const float startTime, const float endTime, const int posX,
						const int posY, char *effect, char *str);/*根据信息打印debug数据表上的信息*/
void static arrset(int *array, const int value, const int numberOfMember);/*数组清空*/

/*StringProcessing.c*/
int getStrHei(unsigned char *str, const int fontSizeSet,
			  const int fontSizeInFile, const char *fontName);/*计算字符串高度*/
int getStrLen(unsigned char *str, const int fontSizeSet,
			  const int fontSizeInFile, const char *fontName);/*计算字符串宽度*/
float strToFloat(char *str);/*字符串（十进制）转化为浮点数*/
int strToInt(char *str);/*字符串（十进制）转化为整数*/
char *strGetLeftPart(char *opStr, char **ipStr, char cutCh);/*得到字符串左边部分，并移动指针至截断位置后一个字符*/
char *deQuotMarks(char *str);/*去字符串左右引号，没有的话则不处理*/
char *deBrackets(char *str);/*去字符串左右括号，没有的话则不处理*/
char *deDesignatedSpace(char *const str, char *startPtr);/*除去指定位置左右空格*/
char *deLeftRightSpace(char *const str);/*除去字符串左右空格*/
char *toLower(char *output, char *input);/*转换成小写字母*/
BOOL isDesignatedChar(char *str, char *designatedChar);/*判断字符串中字符是否都是指定字符*/
char *transcoding(UINT sourceCode, UINT targetCoding,
				  char *const ipStr, char *const opStr, int sizeOfOp);/*利用WINAPI进行编码相互转换*/
BOOL isUtf8(char const *const str);/*判断一个字符串是否是utf-8*/

/*ListProcessing.c*/
int sortList(DANMAKU **listHead);/*排序整个链表（桶排序）*/
void freeList(DANMAKU *listHead);/*释放整个链表*/
void transListCoding(DANMAKU *listHead, UINT targetCoding);/*转换整个弹幕池的文本编码*/

#endif
