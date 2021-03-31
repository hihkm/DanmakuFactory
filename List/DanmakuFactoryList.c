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

#include "DanmakuFactoryList.h"

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
        status -> function = (void *)sortList;
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

    DANMAKU **bucket = NULL, *now = NULL, *last = NULL, *ptr = NULL;
    int cnt, index, danmakuNum = 0, bucketNum = 0;
    float max, min;
    BOOL isSorted = TRUE;

    /* 统计弹幕数量并找出最大最小值 */
    now = *listHead;
    while(now != NULL)
    {
        if(now == *listHead)
        {
            max = min = (*listHead) -> time;
        }
        else
        {
            if(now -> time > max)
            {
                max = now -> time;
            }
            else if(now -> time < min)
            {
                min = now -> time;
            }
        }

        if (isSorted == TRUE && now -> next != NULL && now->time > now->next->time+EPS)
        {
            isSorted = FALSE;
        }
        danmakuNum++;
        now = now -> next;
    }

    /* 如果本来就排序好了直接退出 */
    if (isSorted == TRUE)
    {
        return 0;
    }

    /* 申请桶空间并清0 */
    now = *listHead;
    bucketNum = danmakuNum / 128 + 1;
    if((bucket = (DANMAKU **)malloc(sizeof(DANMAKU *) * bucketNum)) == NULL)
    {
        #if PRINT_ERR == TRUE
        printf("\n[X] 申请内存空间失败");
        #endif
        return 2;
    }
    memset(bucket, 0, sizeof(DANMAKU *) * bucketNum);

    /* 入桶 */
    while(*listHead != NULL)
    {
        index = (int)((now -> time - min) / (max - min + 1) * bucketNum);
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
            if(now -> time < ptr -> time)
            {/* 判断是否为该桶最小值 */
                now -> next = ptr;
                bucket[index] = now;
            }
            else
            {
                ptr = ptr -> next;
                while(ptr != NULL && now -> time > ptr -> time - EPS)
                {/* 即ptr != NULL && now->time >= ptr->time */
                    last = ptr;
                    ptr = ptr -> next;
                }
                now -> next = ptr;
                last -> next = now;
            }
        }
        now = *listHead;

        /* 刷新status */
        if (status != NULL)
        {
            (status -> completedNum)++;
        }
    }/* 结束 while */

    /* 出桶 */
    now = *listHead = NULL;
    for(cnt = 0; cnt < bucketNum; cnt++)
    {
        ptr = bucket[cnt];

        if(ptr != NULL)
        {
            if(*listHead == NULL)
            {
                *listHead = now = ptr;
            }
            else
            {
                now -> next = ptr;
            }
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
void blockByType(DANMAKU *const danmakuHead, const int mode, const char **const keyStrings)
{
    if (mode == 0)
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

        ptr = ptr -> next;
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
