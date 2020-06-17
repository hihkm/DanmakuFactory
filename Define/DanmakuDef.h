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

#ifndef __DANMAKUDEF_H__
#define __DANMAKUDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_OF_TYPE 5
#define EPS 1e-4
#define MAX_TEXT_LENGTH 1024
#define FONTNAME_LEN 128

#define TRUE 1
#define FALSE 0

#define PRINT_ERR FALSE

#define BLK_R2L     1
#define BLK_L2R     2
#define BLK_TOP     4
#define BLK_BOTTOM  8
#define BLK_SPECIAL 16
#define BLK_COLOR   32
#define BLK_REPEAT  64

#define TABLE 1
#define HISTOGRAM 2

#define IS_R2L(ptr) (ptr -> type == 1 || ptr -> type == -1)
#define IS_L2R(ptr) (ptr -> type == 2 || ptr -> type == -2)
#define IS_TOP(ptr) (ptr -> type == 3 || ptr -> type == -3)
#define IS_BTM(ptr) (ptr -> type == 4 || ptr -> type == -4)
#define IS_SPECIAL(ptr) (ptr -> type == 5 || ptr -> type == -5)
#define IS_NORMAL(ptr) (IS_R2L(ptr) || IS_L2R(ptr) || IS_TOP(ptr) || IS_BTM(ptr))

struct SingleDanmaku
{/*弹幕节点定义*/
    float time;            /*开始时间*/ 
    short type;            /*弹幕类型*/ 
    short fontSize;        /*字体大小 25是基准*/ 
    int color;             /*文字颜色*/ 
    char *text;            /*文本内容*/
    struct SpecialDanmakuPart *special;/*特殊弹幕部分*/ 
    struct SingleDanmaku *next;
};

/*特殊弹幕部分属性*/
struct SpecialDanmakuPart
{
    float existTime;         /*生存时间  s*/
    int moveTime;            /*移动时间  ms*/
    int pauseTime;           /*暂停时间  ms*/
    float startX;            /*开始X坐标 小数0-1表比例*/
    float startY;            /*开始Y坐标 小数0-1表比例*/
    float endX;              /*结束X坐标 小数0-1表比例*/
    float endY;              /*结束Y坐标 小数0-1表比例*/
    int fadeStart;           /*渐变开始不透明度 0-255 越大越透明*/ 
    int fadeEnd;             /*渐变结束不透明度 0-255 越大越透明*/ 
    int frY;                 /*Y轴旋转*/ 
    int frZ;                 /*Z轴旋转*/ 
    char fontName[FONTNAME_LEN];/*字体名*/
};

typedef int BOOL;
typedef struct SingleDanmaku DANMAKU;
typedef struct SpecialDanmakuPart SPPART;

#ifdef __cplusplus
}
#endif

#endif
