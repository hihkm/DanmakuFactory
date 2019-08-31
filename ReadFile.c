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

/*弹幕类型重定义规范*/
/*+----------+---------+*/
/*| 类型名称 |  编号   |*/
/*+----------+---------+*/
/*| 右左滚动 |    1    |*/
/*+----------+---------+*/
/*| 左右滚动 |    2    |*/
/*+----------+---------+*/
/*| 上方固定 |    3    |*/
/*+----------+---------+*/
/*| 下方固定 |    4    |*/
/*+----------+---------+*/
/*| 特殊弹幕 |    5    |*/
/*+----------+---------+*/


/*
读取xml文件加入弹幕池 
参数：
文件名/链表头/读取模式（"n"清空新建 / "a"尾部追加）/时轴偏移量 
返回值：
0 正常退出
1 打开文件失败 
2 3 4 读取文件发生错误
5 节点空间申请失败
6 文本部分空间申请失败
7 文件未能按正确格式读入 
*/
int readXml(const char *ipFile, DANMAKU **head, const char *mode, const float timeShift)
{
	FILE *ipF;
	DANMAKU *now = NULL, *last = NULL;
	int cnt;
	
	/*打开文件*/
	if((ipF = fopen(ipFile, "r")) == NULL)
	{
		#if PRINT_ERR == TRUE
		printf("\n[X] 文件打开失败"); 
		#endif
		return 1;
	}
	
	/*判断读入方式*/
	if(*head == NULL || *mode == 'n')
	{/*新建模式*/
		freeList(*head);
		*head = NULL;
	}
	else if(*mode == 'a')
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
	float max, min;
	BOOL sort = FALSE;
	int num = 0;
	int n1Total = 0, n6Total = 0, n4Total = 0, n5Total = 0, n7Total = 0, allTotal = 0; 
	
	while(!feof(ipF))
	{
		/*寻找每条弹幕的开始*/
		while(fgetc(ipF) != '<' || fgetc(ipF) != 'd')
		{
			if(feof(ipF))
			{
				goto ENDREAD;
			}
			if(ferror(ipF))
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
		while(fgetc(ipF) != '>')
		{
			if(feof(ipF))
			{
				goto ENDREAD;
			}
			if(ferror(ipF))
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
		while((ch = fgetc(ipF)) != '<' && cnt < MAX_TEXT_LENGTH - 1)
		{
			t_text[cnt] = ch;
			if(feof(ipF))
			{
				break;
			}
			if(ferror(ipF))
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
		if((now = (DANMAKU *)malloc(sizeof(DANMAKU))) == NULL)
		{
			errorExit(ipF, *head, last);
			#if PRINT_ERR == TRUE
			printf("\n[X] 申请内存空间失败"); 
			#endif
			return 5;
		}
		/*申请文本部分的空间*/ 
		if((now -> text = (char *)malloc(strlen(t_text) + 1)) == NULL)
		{
			errorExit(ipF, *head, now);
			#if PRINT_ERR == TRUE
			printf("\n[X] 申请内存空间失败"); 
			#endif
			return 6;
		}
		
		if(*head == NULL)
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
		switch(t_type)
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
		if(t_time + timeShift < TIME_EPS)
		{
			now -> time = 0.00;
		}
		else
		{
			now -> time = t_time + timeShift;
		}
		now -> fontSize = t_fontSize;
		now -> color = t_color;
		strcpy(now -> text, t_text);
		
		last -> next = now;
		last = now;
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
		return 7;
	}
	fclose(ipF);
	return 0;
}

/*
出错后程序退出前的处理
参数： 
文件指针/链表头指针/最后一个未结尾节点指针/
*/
void static errorExit(FILE *ipF, DANMAKU *head, DANMAKU *ptr)
{
	fclose(ipF);
	if(head != NULL)
	{
		ptr -> next = NULL;
		freeList(head);
	}
	return;
}
