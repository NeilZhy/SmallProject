#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"chess.h"

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
	char board[LINE][LIST];
	int input = 1;
	int a = 0;
	srand((unsigned int)time(NULL));
	
	while (input)
	{
		memset(board, ' ', sizeof(char)*LINE*LIST);
		menu();
		scanf("%d", &input);
		printf("\n");
		switch (input)
		{
		case 1:a = game(board);
			break;
		case 0:break;
		default:printf("������벻����Ҫ������������>:"); break;
		}
		if (0 == input)
		{
			break;
		}	
	}
	printf("��Ϸ��������ӭ�ٴ�ʹ��!!!\n");
	return 0;
}