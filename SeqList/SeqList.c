#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"SeqList.h"

//初始化
void InitSeqList(pSeqList ppseqlist)
{
	assert(ppseqlist);
	memset(ppseqlist->arr,0,sizeof(DataType)*MAX);
	ppseqlist->count = 0;
}

//显示顺序表内容
void show(pSeqList ppseqlist)
{
	int i = 0;
	assert(ppseqlist);
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return;
	}
	for (i = 0; i < ppseqlist->count; i++)
	{
		printf("%d ", ppseqlist->arr[i]);
	}

}

//从后面放入一个数据
void PushBack(pSeqList ppseqlist)
{
	DataType data = 0;
	assert(ppseqlist);
	if ((ppseqlist->count) == MAX)
	{
		printf("空间已满，请执行其他操作\n");
		return;
	}
	printf("请输入你需要增加的数\n");
	scanf("%d",&data);
	ppseqlist->arr[ppseqlist->count] = data;
	ppseqlist->count++;
}


//从后面取出一个数据
int PopBack(pSeqList ppseqlist)
{
	assert(ppseqlist);
	//判断顺序表是否为空
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return -1;
	}
	ppseqlist->count--;
	return ppseqlist->arr[(ppseqlist->count)];
}


//前面插入一个数据
void PushFront(pSeqList ppseqlist)
{
	DataType data = 0;
	int i = 0;
	assert(ppseqlist);
	if ((ppseqlist->count) == MAX)   //判断空间是否已经满了
	{
		printf("空间已满，请执行其他操作\n");
		return;
	}
	printf("请输入你需要增加的数\n");
	scanf("%d", &data);
	if (0 == ppseqlist->count)    //判断第一个位置是否有数
	{
		ppseqlist->arr[0] = data;
		ppseqlist->count++;
	}
	else
	{
		for (i = (ppseqlist->count) - 1; i >= 0; i--)
		{
			ppseqlist->arr[i + 1] = ppseqlist->arr[i];
		}
		ppseqlist->arr[0] = data;
		ppseqlist->count++;
	}
}

//从前面取出一个数据
int PopFront(pSeqList ppseqlist)
{
	int i = 0;
	int data = ppseqlist->arr[0];
	assert(ppseqlist);
	//判断顺序表是否为空
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return -1;
	}
	for (i = 0; i < (ppseqlist->count)-1; i++)
	{
		ppseqlist->arr[i] = ppseqlist->arr[i + 1];
	}
	ppseqlist->count--;
	return data;
}


//查找某一元素，返回该元素的下标
int Find(pSeqList ppseqlist)
{
	int i = 0;
	int data = 0;
	assert(ppseqlist);
	//判断顺序表是否为空
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return -1;
	}
	printf("请输入你需要查找的数>:");
	scanf("%d", &data);
	for (i = 0; i < ppseqlist->count; i++)
	{
		if (ppseqlist->arr[i] == data)
		{
			return i;
		}
	}
	printf("顺序表中没有该数据\n");
	return -1;
}

void Remove(pSeqList ppseqlist)
{
	int data = 0;
	int i = 0;
	assert(ppseqlist);
	//判断顺序表是否为空
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return;
	}
	printf("请输入你需要删除的数>:");
	scanf("%d", &data);
	for (i = 0; i < (ppseqlist->count); i++)
	{
		if (ppseqlist->arr[i] == data)
		{
			ppseqlist->arr[i] = ppseqlist->arr[i + 1];
			ppseqlist->count--;
			printf("数据已删除\n");

			return;
		}
	}
	printf("顺序表中没有该数据\n");
	return;
}


//清空所有的数据
void RemoveAll(pSeqList ppseqlist)
{
	assert(ppseqlist);
	ppseqlist->count = 0;
	printf("顺序表全部清空\n");
}

//排序
void Sort(pSeqList ppseqlist)
{
	int i = 0, j = ppseqlist->count-1;
	int temp = 0;
	int flag = 0;
	assert(ppseqlist);
	//判断顺序表是否为空
	if (0 == ppseqlist->count)
	{
		printf("顺序表为空\n");
		return;
	}
	for (; j > 0; j--)
	{
		for (i = 0; i <= j; i++)
		{
			if ((ppseqlist->arr[flag]) > (ppseqlist->arr[i]))
			{
				flag = i;
			}
			temp = ppseqlist->arr[flag];
			ppseqlist->arr[flag] = ppseqlist->arr[j];
			ppseqlist->arr[j] = temp;
		}
	}

	printf("排序成功\n");
}