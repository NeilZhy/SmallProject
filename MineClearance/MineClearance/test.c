#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"mine.h"
//1.��һ��ɨ�ף�ɨһ��Ƭ2.���ѡ���Ѷ�3.����

void menu()
{
	printf("***********************\n");
	printf("******  1.play  *******\n");
	printf("******  0.exit  *******\n");
	printf("***********************\n");
	printf("��ѡ����Ӧ������>:");
}

int main()
{
	char PlayerBoard[LINE][LIST];
	char UserBoard[LINE + 2][LIST + 2];
	int input = 1;
	int a = 0;
	srand((unsigned int)time(NULL));

	while (input)
	{
		memset(PlayerBoard, '*', sizeof(char)*LINE*LIST);
		memset(UserBoard, '0', sizeof(char)*(LINE+2)*(LIST+2));
		menu();
		scanf("%d", &input);
		printf("\n");
		switch (input)
		{
		case 1:a = game(UserBoard, PlayerBoard);
			break;
		case 0:break;    //�˴�break�������ǽ���switch
		default:printf("������벻����Ҫ������������>:"); break;
		}
		if (0 == input)
		{
			break;      //�˴�break������������whileѭ������������Ϸ
		}
	}
	printf("��Ϸ��������ӭ�ٴ�ʹ��!!!\n");
	return 0;
}