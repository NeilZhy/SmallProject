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
	printf("请选择相应的数字>:");
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
		default:printf("你的输入不符合要求，请重新输入>:"); break;
		}
		if (0 == input)
		{
			break;
		}	
	}
	printf("游戏结束，欢迎再次使用!!!\n");
	return 0;
}