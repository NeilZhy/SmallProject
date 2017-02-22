#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"SeqList.h"

void menu()
{
	printf("\n");
	printf("**********************************\n");
	printf("****1.PushBack  2. PopBack  ******\n");
	printf("****3.PushFront 4.PopFront  ******\n");
	printf("****5.Show      6.Find      ******\n");
	printf("****7.Remove    8.RemoveAll ******\n");
	printf("****9.Sort      10.BinSearch******\n");
	printf("****        0. exit         ******\n");
	printf("***********************\n");
}

void test(pSeqList ppseqlist)
{
	int input = 0;
	int data = 0;
	do
	{
		menu(); 
		printf("请选择>:");
		scanf("%d",&input);
		switch (input)
		{
		case 1:PushBack(ppseqlist);
			//show(ppseqlist);
			break;
		case 2:data = PopBack(ppseqlist);
			printf("从后面取得的一个数是 %d",data);
			break;
		case 3:PushFront(ppseqlist);
			break;
		case 4:data = PopFront(ppseqlist);
			printf("从前面取得的一个数是 %d", data);
			break;
		case 5:show(ppseqlist);
			break;
		case 6:data = Find(ppseqlist);
			printf("该数据的下标为 %d\n",data);
			break;
		case 7:Remove(ppseqlist);
			break; 
		case 8:RemoveAll(ppseqlist);
			break;
		case 9:Sort(ppseqlist);
			break;
		default:printf("程序结束\n");
		}

	} while (0 != input);
	
}

int main()
{
	SeqList seqlist;
	InitSeqList(&seqlist);
	test(&seqlist);
	system("pause");
	return 0;
}