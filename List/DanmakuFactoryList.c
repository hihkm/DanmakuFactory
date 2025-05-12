/* MIT License
 * 
 * Copyright (c) 2022 hkm
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "DanmakuFactoryList.h"
#include "../Config/Config.h"
#include "../Define/DanmakuDef.h"

/*
 * 排序整个链表（桶排序）
 * 参数：要排序的链表头
 * 返回值：
 * 0 正常退出
 * 1 弹幕池为空
 * 2 桶空间申请失败
  */
int sortList(DANMAKU **listHead, STATUS *const status)
{
    /* 刷新status */
    if (status != NULL)
    {
        status -> function = (void *)&sortList;
        (status -> completedNum) = 0;
        status -> isDone = FALSE;
    }

    if(*listHead == NULL)
    {
        #if PRINT_ERR == TRUE
        printf("\n[X] 弹幕池为空");
        #endif
        return 1;
    }

    DANMAKU *now = (*listHead)->next;
    BOOL isSorted = TRUE;

    /* 统计弹幕数量并找出最大最小值 */
    int danmakuNum = 1; // 弹幕条数
    int max;            // 最大值
    int min;            // 最小值
    for (max = min = (*listHead) -> time; now != NULL; now = now -> next, ++danmakuNum)
    {
        if(now -> time > max)
        {
            max = now -> time;
        }
        else if(now -> time < min)
        {
            min = now -> time;
        }

        if (isSorted == TRUE && now -> next != NULL && now->time > now->next->time)
        {
            isSorted = FALSE;
        }
    }

    /* 如果本来就排序好了直接退出 */
    if (isSorted == TRUE)
    {
        return 0;
    }

    /* 申请桶空间并清0 */
    int bucketNum = danmakuNum / 128 + 1;
    DANMAKU **bucket = NULL;
    if((bucket = (DANMAKU **)malloc(sizeof(DANMAKU *) * bucketNum)) == NULL)
    {
        #if PRINT_ERR == TRUE
        printf("\n[X] 申请内存空间失败");
        #endif
        return 2;
    }
    memset(bucket, 0, sizeof(DANMAKU *) * bucketNum);

    /* 入桶 */
    int index;  // 桶号
    double denominator = max - min + 1;
    DANMAKU *ptr;
    DANMAKU *last;
    do{
        now = *listHead;
        index = (int)(bucketNum * ((now->time - min) / denominator));
        if (index >= bucketNum || index < 0) {
            /* 溢出非法索引处理 */
            index = bucketNum - 1;
        }

        *listHead = (*listHead) -> next;
        if(bucket[index] == NULL)
        {/* 如果该桶为空则将新节点指针填入 */
            bucket[index] = now;
            now -> next = NULL;
        }
        else
        {
            ptr = last = bucket[index];
            if(now -> time <= ptr -> time)
            {/* 判断是否为该桶最小值 */
                bucket[index] = now;
            }
            else
            {
                while ((ptr = ptr -> next) != NULL && now->time > ptr->time)
                {
                    last = ptr;
                }
                last -> next = now;
            }
            now -> next = ptr;
        }

        /* 刷新status */
        if (status != NULL)
        {
            (status -> completedNum)++;
        }
    } while (*listHead != NULL);

    /* 出桶 */
    now = *listHead = bucket[0];
    while (now->next != NULL) {
        now = now->next;
    }
    for (int cnt = 1; cnt < bucketNum; cnt++)
    {
        ptr = bucket[cnt];
        if(ptr != NULL)
        {
            now -> next = ptr;
            while(ptr -> next != NULL)
            {
                ptr = ptr -> next;
            }
            now = ptr;
        }
    }
    free(bucket);

    /* 刷新status */
    if (status != NULL)
    {
        status -> isDone = TRUE;
    }
    return 0;
}

/*
 * 弹幕按类型屏蔽
 * 参数：弹幕链表头/屏蔽模式/屏蔽关键字串集
 * 返回值：空
 * 附屏蔽模式：
 * BLK_R2L         屏蔽右左滚动
 * BLK_L2R         屏蔽左右滚动
 * BLK_TOP         屏蔽顶端固定
 * BLK_BOTTOM      屏蔽底端固定
 * BLK_SPECIAL     屏蔽特殊弹幕
 * BLK_COLOR       屏蔽非白色弹幕
  */
void blockByType(DANMAKU *const danmakuHead, const int mode, char** keyStrings)
{
    if (mode == 0 && keyStrings == NULL)
    {
        return;
    }

    DANMAKU *ptr = (DANMAKU *)danmakuHead;
    while (ptr != NULL)
    {
        if ((mode & BLK_COLOR) && !IS_SPECIAL(ptr) && ptr -> color != 0xFFFFFF)
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        else if ((mode & BLK_R2L) && IS_R2L(ptr))
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        else if ((mode & BLK_L2R) && IS_L2R(ptr))
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        else if ((mode & BLK_TOP) && IS_TOP(ptr))
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        else if ((mode & BLK_BOTTOM) && IS_BTM(ptr))
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        else if ((mode & BLK_SPECIAL) && IS_SPECIAL(ptr))
        {
            if (ptr -> type > 0)
            {
                ptr -> type *= -1;
            }
        }
        //TODO:关键字屏蔽以及正则匹配
        // 如果有关键字串集
        if (keyStrings != NULL && ptr -> text != NULL)
        {
            // 逐个检查关键字串
            for (int i = 0; keyStrings[i] != NULL; i++)
            {
                // 如果弹幕文本中包含关键字串
                if (strstr(ptr -> text, keyStrings[i]) != NULL)
                {
                    if (ptr -> type > 0)
                    {
                        ptr -> type *= -1;
                    }
                    break;
                }
            }
        }
        ptr = ptr -> next;
    }

    if (keyStrings != NULL) {
        for (int i = 0; keyStrings[i] != NULL; ++i) {
            free(keyStrings[i]);
        }
    }
}

/*
 * 释放整个链表
 * 参数：
 * 要释放的链表头
  */
void freeList(DANMAKU *listHead)
{
    DANMAKU *ptr = listHead;
    while(ptr != NULL)
    {
        listHead = ptr -> next;
        free(ptr -> text);/* 释放文本部分的空间 */
        free(ptr);
        ptr = listHead;
    }
}

void normFontSize(DANMAKU* const danmakuHead, const CONFIG config)
{
    BOOL doNormalize = FALSE;

    if (config.fontSizeNorm) {
        for (DANMAKU* ptr = (DANMAKU*)danmakuHead; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->type == SPECIAL) {
                continue;
            }

            if (ptr->fontSize <= 0 || ptr->fontSize >= config.resolution.y) {
                doNormalize = TRUE;
                break;
            }
        }
    }

    if (config.fontSizeStrict || doNormalize) {
        for (DANMAKU* ptr = (DANMAKU*)danmakuHead; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->type == SPECIAL) {
                continue;
            }

            ptr->fontSize = 25;
        }
    }
}
