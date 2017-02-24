#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"LinkList.h"
#include<assert.h>

void menu()
{
	printf("\n");
	printf("************************************\n");
	printf("****  1.PushBack  2. PopBack  ******\n");
	printf("****  3.PushFront 4.PopFront  ******\n");
	printf("****  5.Show      6.Find      ******\n");
	printf("****  7.Remove    8.Insert    ******\n");
	printf("****  9.Destroy   10.EraseNotTail***\n");
	printf("****  11.ReverseList1(头插法) ******\n");
	printf("****  12.ReverseList2(数组指针法)***\n");
	printf("****  13.BubbleSortLink       ******\n");
	printf("****  14.InserFroveNode       ******\n");
	printf("****  15.MyMerge  16.Josepfcycle ***\n");
	printf("****  17.CheckCycle 18.CheckNumCycle ***\n");
	printf("****  19.CheckInCycle       ******\n");
	printf("****        0. exit           ******\n");
	printf("************************************\n");
}

void test()
{
	pLinkList plink;
	pLinkList plink2;
	
	pNode node = NULL;
	int input = 0;
	int data = 0;
	InitList(&plink);
	InitList(&plink2);
	do
	{
		menu();
		printf("请选择>:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:PushBack(&plink);
			break;
		case 5:Show(plink);
			break;
		case 2:PopBack(&plink);
			break;
		case 3:PushFront(&plink);
			break;
		case 4:PopFront(&plink);
			break;
		case 6:Find(plink);
			//printf("返回地址所指向的数据是 %d\n",node->data);
			break;
		case 7:Remove(&plink);
			break;
		case 8:Insert(&plink);
			break;
		case 9:Destroy(&plink);
			break;
		case 10:EraseNotTail(Find(plink));
			break;
		case 11:ReverseList1(&plink);
			break;
		case 12:
			ReverseList2(&plink);
			break;
		case 13:BubbleSortLink(plink);
			break;
		case 14:InserFroveNode(Find(plink));
			break;
		case 15:MyMerge(&plink, &plink2);
			break;
		case 16:Josepfcycle(&plink, 3);
			break;
		case 17:CheckCycle(plink);
			break;
		case 18:CheckNumCycle(plink);
			break;
		case 19:CheckInCycle(plink);
			break;
		default:printf("输入有误，请重新输入\n");
		}

	} while (0 != input);

}

int main()
{
	test();
	system("pause");
	return 0;
}
