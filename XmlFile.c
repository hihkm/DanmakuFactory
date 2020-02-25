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

#include "CDanmakuFactory.h"

static char *xmlUnescape(char *const str);
static void errorExit(FILE *ipF, DANMAKU *head, DANMAKU *ptr);

/*弹幕类型重定义规范*/
/*+-------------+---------+*/
/*|  类型名称   |  编号   |*/
/*+-------------+---------+*/
/*|  右左滚动   |    1    |*/
/*+-------------+---------+*/
/*|  左右滚动   |    2    |*/
/*+-------------+---------+*/
/*|  上方固定   |    3    |*/
/*+-------------+---------+*/
/*|  下方固定   |    4    |*/
/*+-------------+---------+*/
/*| B站特殊弹幕 |    5    |*/
/*+-------------+---------+*/

/*
 * 读取xml文件加入弹幕池 
 * 参数：
 * 文件名/链表头/读取模式（"n"清空新建 / "a"尾部追加）/时轴偏移量 
 * 返回值：
 * 0 正常退出
 * 1 打开文件失败 
 * 2 3 4 读取文件发生错误
 * 5 6 7 内存空间申请失败
 * 8 文件未能按正确格式读入
 */
int readXml(const char *const ipFile, DANMAKU **head, const char *mode, const float timeShift, STATUS *const status)
{
    FILE *ipF;
    DANMAKU *now = NULL, *last = NULL;
    int cnt;
    
    /*刷新status*/
    if (status != NULL)
    {
        status -> function = (void *)readXml;
        status -> completedNum = 0;
        status -> isDone = FALSE;
    }
    
    /*打开文件*/
    if ((ipF = fopen(ipFile, "r")) == NULL)
    {
        #if PRINT_ERR == TRUE
        printf("\n[X] 文件打开失败"); 
        #endif
        return 1;
    }
    
    /*判断读入方式*/
    if (*head == NULL || *mode == 'n')
    {/*新建模式*/
        freeList(*head);
        *head = NULL;
    }
    else if (*mode == 'a')
    {/*追加模式*/
        now = last = *head;
        if((*head) -> next != NULL)
        {
            while((last -> next) -> next != NULL)
            {
                last = last -> next;
            }
            now = last -> next;
            last -> next = now;
        }
    }
    
    /*读取xml文件*/
    float t_time;
    short t_type;
    short t_fontSize;
    int t_color;
    char ch, t_text[MAX_TEXT_LENGTH];
    char tempText[MAX_TEXT_LENGTH];
    char *textPtr;
    
    while (!feof(ipF))
    {
        /*寻找每条弹幕的开始*/
        while (fgetc(ipF) != '<' || fgetc(ipF) != 'd')
        {
            if (feof(ipF))
            {
                goto ENDREAD;
            }
            if (ferror(ipF))
            {
                errorExit(ipF, *head, last);
                #if PRINT_ERR == TRUE
                printf("\n[X] 读文件发生错误"); 
                #endif
                return 2;
            }
        }
        
        fscanf(ipF, " p=\"%f,%hd,%hd,%d,", &t_time, &t_type, &t_fontSize, &t_color);
        
        /*寻找文本部分的开头*/
        while (fgetc(ipF) != '>')
        {
            if (feof(ipF))
            {
                goto ENDREAD;
            }
            if (ferror(ipF))
            {
                errorExit(ipF, *head, last);
                #if PRINT_ERR == TRUE
                printf("\n[X] 读文件发生错误"); 
                #endif
                return 3;
            }
        }
        
        /*读取文本部分*/ 
        cnt = 0;
        while ((ch = fgetc(ipF)) != '<' && cnt < MAX_TEXT_LENGTH - 1)
        {
            t_text[cnt] = ch;
            if (feof(ipF))
            {
                break;
            }
            if (ferror(ipF))
            {
                errorExit(ipF, *head, last);
                #if PRINT_ERR == TRUE
                printf("\n[X] 读文件发生错误"); 
                #endif
                return 4;
            }
            cnt++;
        }
        t_text[cnt] = '\0';
        
        /*申请一个节点的空间*/
        if ((now = (DANMAKU *)malloc(sizeof(DANMAKU))) == NULL)
        {
            errorExit(ipF, *head, last);
            #if PRINT_ERR == TRUE
            printf("\n[X] 申请内存空间失败"); 
            #endif
            return 5;
        }
        
        /*申请文本部分空间*/
        if ((now -> text = (char *)malloc((strlen(t_text) + 1) * sizeof(char))) == NULL)
        {
            errorExit(ipF, *head, now);
            #if PRINT_ERR == TRUE
            printf("\n[X] 申请内存空间失败"); 
            #endif
            return 6;
        }
        
        if (*head == NULL)
        {
            *head = last = now;
        }
        
        /*+----------+-----------+-----------+*/
        /*| 类型名称 | 原类型编号| 新类型编号|*/
        /*+----------+-----------+-----------+*/
        /*| 右左滚动 |     1     |     1     |*/
        /*+----------+-----------+-----------+*/
        /*| 左右滚动 |     6     |     2     |*/
        /*+----------+-----------+-----------+*/
        /*| 上方固定 |     5     |     3     |*/
        /*+----------+-----------+-----------+*/
        /*| 下方固定 |     4     |     4     |*/
        /*+----------+-----------+-----------+*/
        /*| 特殊弹幕 |     7     |     5     |*/
        /*+----------+-----------+-----------+*/
        switch (t_type)
        {/*将xml定义的类型编号转换为程序统一定义的类型编号（如上表）*/ 
            case 1:
            {
                now -> type = 1;
                break;
            }
            case 6:
            {
                now -> type = 2;
                break;
            }
            case 5:
            {
                now -> type = 3;
                break;
            }
            case 4:
            {
                now -> type = 4;
                break;
            }
            case 7:
            {
                now -> type = 5;
                break;
            }
            default:
            {
                now -> type = t_type;
                break;
            }
        }
        
        /*如果时间加偏移量是负数则置0*/
        if (t_time + timeShift < EPS)
        {
            now -> time = 0.00;
        }
        else
        {
            now -> time = t_time + timeShift;
        }
        now -> fontSize = t_fontSize;
        now -> color = t_color;
        now -> special = NULL;
        xmlUnescape(t_text);/*文本内容反转义*/
        
        /*特殊弹幕文本解析*/
        if (t_type == 7)
        {
            /*申请特殊弹幕部分的空间*/ 
            if ((now -> special = (SPPART *)malloc(sizeof(SPPART))) == NULL)
            {
                errorExit(ipF, *head, now);
                #if PRINT_ERR == TRUE
                printf("\n[X] 申请内存空间失败"); 
                #endif
                return 7;
            }
            char textPart[MAX_TEXT_LENGTH];
            textPtr = t_text;
            /*[0,0.17,"1-1",7,"文本部分内容",0,0,0,0.17,500,0,true,"微软雅黑",1]*/
            strGetLeftPart(NULL, &textPtr, '[', MAX_TEXT_LENGTH);
            now->special->startX = atof(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->startY = atof(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->fadeStart = (int)((1-atof(deQuotMarks(strGetLeftPart(tempText,&textPtr,'-',MAX_TEXT_LENGTH)))) * 255);
            now->special->fadeEnd = (int)((1-atof(deQuotMarks(strGetLeftPart(tempText,&textPtr,',',MAX_TEXT_LENGTH)))) * 255);
            now->special->existTime = atof(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            
            /*文本部分*/
            strGetLeftPart(NULL, &textPtr, '\"', MAX_TEXT_LENGTH);
            strGetLeftPart(textPart, &textPtr, '\"', MAX_TEXT_LENGTH);
            deQuotMarks(textPart);
            strGetLeftPart(NULL, &textPtr, ',', MAX_TEXT_LENGTH);
            
            now->special->frZ = atoi(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->frY = atoi(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->endX = atof(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->endY = atof(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->moveTime = atoi(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            now->special->pauseTime = atoi(strGetLeftPart(tempText, &textPtr, ',', MAX_TEXT_LENGTH));
            
            /*字体部分*/ 
            strGetLeftPart(NULL, &textPtr, '\"', MAX_TEXT_LENGTH);
            strGetLeftPart(now->special->fontName, &textPtr, '\"', MAX_TEXT_LENGTH);
            deQuotMarks(now->special->fontName);
            strSafeCopy(t_text, textPart, MAX_TEXT_LENGTH);
        }
        strcpy(now -> text, t_text);
        
        last -> next = now;
        last = now;
        
        /*更新状态*/
        if (status != NULL)
        {
            (status->totalNum)++;
            (status->completedNum)++;
        }
    }/*结束 while*/
    ENDREAD:
    if (now != NULL)
    {
        now -> next = NULL;
    }
    else
    {
        #if PRINT_ERR == TRUE
        printf("\n[X] 文件不能按正确格式读入"); 
        #endif
        return 8;
    }
    
    fclose(ipF);
    
    /*刷新status*/
    if (status != NULL)
    {
        status -> isDone = TRUE;
    }
    return 0;
}

/*
 * 写xml文件
 * 参数：文件名/弹幕池/状态
 * 返回值：
 * 0 正常退出
 * 1 弹幕池为空
 * 2 创建文件失败
 * 3 写文件发生错误
 */
int writeXml(char const *const fileName, DANMAKU *danmakuHead, STATUS *const status)
{
    /*刷新status*/
    if (status != NULL)
    {
        status -> function = (void *)writeXml;
        (status -> completedNum) = 0;
        status -> isDone = FALSE;
    }
    
    if (danmakuHead == NULL)
    {
        return 1;
    }
    
    FILE *opF;
    DANMAKU *ptr = danmakuHead;
    
    char tempText[64]; 
    int typeInXml;
    
    if ((opF = fopen(fileName, "w")) == NULL)
    {
        return 2;
    }
    fprintf(opF, "<?xml version=\"1.0\"?>"
                 "\n<i>"
           );

    fprintf(opF, "\n    <chatserver></chatserver>"
                 "\n    <chatid></chatid>"
                 "\n    <mission></mission>"
                 "\n    <maxlimit></maxlimit>"
                 "\n    <state></state>"
                 "\n    <real_name></real_name>"
                 "\n    <source></source>"
           );
    
    while (ptr != NULL)
    {
        /*+----------+-----------+-----------+*/
        /*| 类型名称 | 原类型编号| 新类型编号|*/
        /*+----------+-----------+-----------+*/
        /*| 右左滚动 |     1     |     1     |*/
        /*+----------+-----------+-----------+*/
        /*| 左右滚动 |     6     |     2     |*/
        /*+----------+-----------+-----------+*/
        /*| 上方固定 |     5     |     3     |*/
        /*+----------+-----------+-----------+*/
        /*| 下方固定 |     4     |     4     |*/
        /*+----------+-----------+-----------+*/
        /*| 特殊弹幕 |     7     |     5     |*/
        /*+----------+-----------+-----------+*/
        if (IS_R2L(ptr))
        {
            typeInXml = 1;
        }
        else if (IS_L2R(ptr))
        {
            typeInXml = 6;
        }
        else if (IS_TOP(ptr))
        {
            typeInXml = 5;
        }
        else if (IS_BTM(ptr))
        {
            typeInXml = 4;
        }
        else if (IS_SPECIAL(ptr))
        {
            typeInXml = 7;
        }
        else
        {
            ptr = ptr -> next;
            continue;
        }
        fprintf(opF, "\n    <d p=\"%s,%d,%d,%d,,0,,\">",
                     floatToStr(tempText, ptr -> time, 3),
                     typeInXml, ptr->fontSize, ptr->color
               );
        
        if (IS_SPECIAL(ptr) == FALSE)
        {
            fprintf(opF, "%s", ptr -> text);
        }
        else
        {
            fprintf(opF, "[%s,", floatToStr(tempText, ptr->special -> startX, 2));
            fprintf(opF, "%s,", floatToStr(tempText, ptr->special -> startY, 2));
            fprintf(opF, "\"%s", floatToStr(tempText, 1 - (ptr->special->fadeStart / 255.00), 2));
            fprintf(opF, "-%s\",", floatToStr(tempText, 1 - (ptr->special->fadeEnd / 255.00), 2));
            fprintf(opF, "%s,", floatToStr(tempText, ptr->special -> existTime, 1));
            fprintf(opF, "\"%s\",", ptr->text);
            fprintf(opF, "%d,%d,", ptr->special -> frZ, ptr->special -> frY);
            fprintf(opF, "%s,", floatToStr(tempText, ptr->special -> endX, 2));
            fprintf(opF, "%s,", floatToStr(tempText, ptr->special -> endY, 2));
            fprintf(opF, "%d,%d,", ptr->special -> moveTime, ptr->special -> pauseTime);
            fprintf(opF, "true,\"%s\",1]", ptr->special -> fontName);
        }
        fprintf(opF, "</d>");
        
        ptr = ptr -> next;
        
        if(ferror(opF))
        {
            #if PRINT_ERR == TRUE
            printf("\n[X] 写出文件时发生错误");
            #endif
            fclose(opF);
            return 3;
        }
        
        /*刷新status*/
        if (status != NULL)
        {
            (status -> completedNum)++;
        }
    }
    
    fprintf(opF, "\n</i>");
    
    fclose(opF);
    
    /*刷新status*/
    if (status != NULL)
    {
        status -> isDone = TRUE;
    }
    return 0;
}


/*
 * xml转义字符反转义
 * 
 * 对照： 
 *     原      反转义
 *    &lt;        <
 *    &gt;        >
 *    &amp;       &
 *    &apos;      '
 *    &quot;      " 
 */
static char *xmlUnescape(char *const str)
{
    char *leftPtr, *rightPtr, *reWritePtr;
    leftPtr = str;
    while (*leftPtr != '\0')
    {
        if (*leftPtr == '&')
        {
            if (strstr(leftPtr, "&amp;") == leftPtr)
            {
                *leftPtr = '&';
                reWritePtr = leftPtr + 1;
                rightPtr = leftPtr + 5;
                while (*rightPtr != '\0')
                {
                    *reWritePtr = *rightPtr;
                    reWritePtr++;
                    rightPtr++;
                }
                *reWritePtr = '\0';
            }
            else if (strstr(leftPtr, "&apos;") == leftPtr)
            {
                *leftPtr = '\'';
                reWritePtr = leftPtr + 1;
                rightPtr = leftPtr + 6;
                while (*rightPtr != '\0')
                {
                    *reWritePtr = *rightPtr;
                    reWritePtr++;
                    rightPtr++;
                }
                *reWritePtr = '\0';
            }
            else if (strstr(leftPtr, "&gt;") == leftPtr)
            {
                *leftPtr = '>';
                reWritePtr = leftPtr + 1;
                rightPtr = leftPtr + 4;
                while (*rightPtr != '\0')
                {
                    *reWritePtr = *rightPtr;
                    reWritePtr++;
                    rightPtr++;
                }
                *reWritePtr = '\0';
            }
            else if (strstr(leftPtr, "&lt;") == leftPtr)
            {
                *leftPtr = '<';
                reWritePtr = leftPtr + 1;
                rightPtr = leftPtr + 4;
                while (*rightPtr != '\0')
                {
                    *reWritePtr = *rightPtr;
                    reWritePtr++;
                    rightPtr++;
                }
                *reWritePtr = '\0';
            }
            else if (strstr(leftPtr, "&quot;") == leftPtr)
            {
                *leftPtr = '\"';
                reWritePtr = leftPtr + 1;
                rightPtr = leftPtr + 6;
                while (*rightPtr != '\0')
                {
                    *reWritePtr = *rightPtr;
                    reWritePtr++;
                    rightPtr++;
                }
                *reWritePtr = '\0';
            }
        }
        
        leftPtr++;
    }
    
    return str;
}

/*
 * 出错后程序退出前的处理
 * 参数： 
 * 文件指针/链表头指针/最后一个未结尾节点指针/
 */
static void errorExit(FILE *ipF, DANMAKU *head, DANMAKU *ptr)
{
    fclose(ipF);
    if(head != NULL)
    {
        ptr -> next = NULL;
        ptr -> special = NULL;
        freeList(head);
    }
    return;
}
