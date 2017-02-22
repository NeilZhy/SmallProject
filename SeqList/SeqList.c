#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"SeqList.h"

//��ʼ��
void InitSeqList(pSeqList ppseqlist)
{
	assert(ppseqlist);
	memset(ppseqlist->arr,0,sizeof(DataType)*MAX);
	ppseqlist->count = 0;
}

//��ʾ˳�������
void show(pSeqList ppseqlist)
{
	int i = 0;
	assert(ppseqlist);
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
		return;
	}
	for (i = 0; i < ppseqlist->count; i++)
	{
		printf("%d ", ppseqlist->arr[i]);
	}

}

//�Ӻ������һ������
void PushBack(pSeqList ppseqlist)
{
	DataType data = 0;
	assert(ppseqlist);
	if ((ppseqlist->count) == MAX)
	{
		printf("�ռ���������ִ����������\n");
		return;
	}
	printf("����������Ҫ���ӵ���\n");
	scanf("%d",&data);
	ppseqlist->arr[ppseqlist->count] = data;
	ppseqlist->count++;
}


//�Ӻ���ȡ��һ������
int PopBack(pSeqList ppseqlist)
{
	assert(ppseqlist);
	//�ж�˳����Ƿ�Ϊ��
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
		return -1;
	}
	ppseqlist->count--;
	return ppseqlist->arr[(ppseqlist->count)];
}


//ǰ�����һ������
void PushFront(pSeqList ppseqlist)
{
	DataType data = 0;
	int i = 0;
	assert(ppseqlist);
	if ((ppseqlist->count) == MAX)   //�жϿռ��Ƿ��Ѿ�����
	{
		printf("�ռ���������ִ����������\n");
		return;
	}
	printf("����������Ҫ���ӵ���\n");
	scanf("%d", &data);
	if (0 == ppseqlist->count)    //�жϵ�һ��λ���Ƿ�����
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

//��ǰ��ȡ��һ������
int PopFront(pSeqList ppseqlist)
{
	int i = 0;
	int data = ppseqlist->arr[0];
	assert(ppseqlist);
	//�ж�˳����Ƿ�Ϊ��
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
		return -1;
	}
	for (i = 0; i < (ppseqlist->count)-1; i++)
	{
		ppseqlist->arr[i] = ppseqlist->arr[i + 1];
	}
	ppseqlist->count--;
	return data;
}


//����ĳһԪ�أ����ظ�Ԫ�ص��±�
int Find(pSeqList ppseqlist)
{
	int i = 0;
	int data = 0;
	assert(ppseqlist);
	//�ж�˳����Ƿ�Ϊ��
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
		return -1;
	}
	printf("����������Ҫ���ҵ���>:");
	scanf("%d", &data);
	for (i = 0; i < ppseqlist->count; i++)
	{
		if (ppseqlist->arr[i] == data)
		{
			return i;
		}
	}
	printf("˳�����û�и�����\n");
	return -1;
}

void Remove(pSeqList ppseqlist)
{
	int data = 0;
	int i = 0;
	assert(ppseqlist);
	//�ж�˳����Ƿ�Ϊ��
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
		return;
	}
	printf("����������Ҫɾ������>:");
	scanf("%d", &data);
	for (i = 0; i < (ppseqlist->count); i++)
	{
		if (ppseqlist->arr[i] == data)
		{
			ppseqlist->arr[i] = ppseqlist->arr[i + 1];
			ppseqlist->count--;
			printf("������ɾ��\n");

			return;
		}
	}
	printf("˳�����û�и�����\n");
	return;
}


//������е�����
void RemoveAll(pSeqList ppseqlist)
{
	assert(ppseqlist);
	ppseqlist->count = 0;
	printf("˳���ȫ�����\n");
}

//����
void Sort(pSeqList ppseqlist)
{
	int i = 0, j = ppseqlist->count-1;
	int temp = 0;
	int flag = 0;
	assert(ppseqlist);
	//�ж�˳����Ƿ�Ϊ��
	if (0 == ppseqlist->count)
	{
		printf("˳���Ϊ��\n");
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

	printf("����ɹ�\n");
}