#ifndef __DANMAKU_FACTORY_H__
#define __DANMAKU_FACTORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define VERSION "1.11"
#define NUM_OF_TYPE 5 
#define TIME_EPS 1e-4
#define MAX_TEXT_LENGTH 1024

#define TRUE 1
#define FALSE 0

#define PRINT_ERR TRUE

#define IS_R2L(ptr) (ptr -> type == 1 || ptr -> type == -1)
#define IS_L2R(ptr) (ptr -> type == 2 || ptr -> type == -2)
#define IS_TOP(ptr) (ptr -> type == 3 || ptr -> type == -3)
#define IS_BTM(ptr) (ptr -> type == 4 || ptr -> type == -4)
#define IS_SPECIAL(ptr) (ptr -> type == 5 || ptr -> type == -5)
#define IS_NORMAL(ptr) (IS_R2L(ptr) || IS_L2R(ptr) || IS_TOP(ptr) || IS_BTM(ptr) || IS_SPECIAL(ptr))

typedef short BOOL;

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
int ReadXml(const char *ipFile, DANMAKU **head, const char *mode, const float timeShift);
void ErrorExit(FILE *ipF, DANMAKU *head, DANMAKU *ptr);

/*WriteFile.c*/
int WriteAss(const char *opFileName, DANMAKU *head, const int resX, const int resY, const int fontSize,
			 char *fontName,const int shadow, const int outline, const float speed, const float holdTime, 
			 const int density ,const int opacity, const int blank, char *shieldMode, char *debugMode);
int WriteAssDebugPath(const char *opFileName, DANMAKU *head, char *mode, const int speed, const int holdTime,
					  char *shieldMode);
float GetEndTime(DANMAKU *danmakuPtr, const int speed, const int holdTime);
int PrintTime(FILE *filePtr, float time, char *endText);
char *ToHexColor(int decColor, char *hexColor);
char *ToHexOpacity(int decOpacity, char *hexOpacity);
int FindMin(float *array, const int numOfLine, const int stopSubScript, const int mode);
int DrawRectangle(FILE *opF, int startX, int startY, int width, int height);
int PrintDebugDataInt(FILE *filePtr, const float startTime, const float endTime, const int posX, const int posY,
					  char *effect, const int data);
int PrintDebugDataStr(FILE *filePtr, const float startTime, const float endTime, const int posX, const int posY,
					  char *effect, char *str);
void arrset(int *array, const int value, const int numberOfMember);

/*StringProcessing.c*/
int GetStrHei(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName);
int GetStrLen(unsigned char *str, const int fontSizeSet, const int fontSizeInFile, const char *fontName);
float StrToFloat(char *str);
int StrToInt(char *str);
char *StrGetLeftPart(char *opStr, char **ipStr, char cutCh);
char *DeQuotMarks(char *str);

/*ListProcessing.c*/
int SortList(DANMAKU **listHead);
void FreeList(DANMAKU *listHead);

#endif
