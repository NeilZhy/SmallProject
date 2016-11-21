#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"mine.h"
//1.第一次扫雷，扫一大片2.玩家选择难度3.插标记

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
		case 0:break;    //此处break的作用是结束switch
		default:printf("你的输入不符合要求，请重新输入>:"); break;
		}
		if (0 == input)
		{
			break;      //此处break的作用是跳出while循环，即结束游戏
		}
	}
	printf("游戏结束，欢迎再次使用!!!\n");
	return 0;
}