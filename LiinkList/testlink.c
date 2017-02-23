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
	printf("****  9.Destroy   10.Erase    ******\n");
	printf("****        0. exit           ******\n");
	printf("************************************\n");
}

void test()
{
	pLinkList plink;
	InitList(&plink);
	pNode node = NULL;
	int input = 0;
	int data = 0;
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
