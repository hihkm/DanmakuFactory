#include "DanmakuFactory.h"

/*
桶排序整理整个链表
参数：
要排序的链表头
返回值：
0 正常退出
1 传入指针为空
2 桶空间申请失败 
*/
int SortList(DANMAKU **listHead)
{
	if(*listHead == NULL)
	{
		return 1;
	}
	
	DANMAKU **bucket = NULL, *now = NULL, *last = NULL, *tail = NULL, *ptr = NULL;
	int cnt, index, danmakuNum = 0, bucketNum = 0;
	float max, min;
	
	/*统计弹幕数量并找出最大最小值*/
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
		danmakuNum++;
		now = now -> next;
	}
	
	/*申请桶空间并清0*/
	now = *listHead;
	bucketNum = danmakuNum / 128 + 1;
	if((bucket = (DANMAKU **)malloc(sizeof(DANMAKU *) * bucketNum)) == NULL)
	{
		return 2;
	}
	memset(bucket, 0, sizeof(DANMAKU *) * bucketNum);
	
	/*入桶*/ 
	while(*listHead != NULL)
	{
		index = (now -> time - min) / (max - min + 1) * bucketNum;
		*listHead = (*listHead) -> next;
		if(bucket[index] == NULL)
		{/*如果该桶为空则将新节点指针填入*/ 
			bucket[index] = now;
			now -> next = NULL;
		}
		else
		{
			ptr = last = bucket[index];
			if(now -> time < ptr -> time)
			{/*判断是否为该桶最小值*/ 
				now -> next = ptr;
				bucket[index] = now;
			}
			else
			{
				ptr = ptr -> next;
				while(ptr != NULL && now -> time > ptr -> time - TIME_EPS)
				{/*即ptr != NULL && now->time >= ptr->time*/
					last = ptr;
					ptr = ptr -> next;
				}
				now -> next = ptr;
				last -> next = now;
			}
		}
		now = *listHead;
	}/*结束 while*/
	
	/*出桶*/
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
	return 0; 
}


/*
释放整个链表
参数：
要free掉的链表头
*/
void FreeList(DANMAKU *listHead)
{
	DANMAKU *ptr = listHead;
	while(ptr != NULL)
	{
		listHead = ptr -> next;
		free(ptr -> text);/*释放文本部分的空间*/ 
		free(ptr);
		ptr = listHead;
	}
}
