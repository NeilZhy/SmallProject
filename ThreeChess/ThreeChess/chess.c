#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"chess.h"

void ChessBoard(char board[LINE][LIST])
{
	printf("%c|%c|%c\n", board[0][0], board[0][1], board[0][2]);
	printf("-----\n");
	printf("%c|%c|%c\n", board[1][0], board[1][1], board[1][2]);
	printf("-----\n");
	printf("%c|%c|%c\n", board[2][0], board[2][1], board[2][2]);
	printf("\n\n");
}

int game(char board[LINE][LIST])
{
	ChessBoard(board);
	while (1)
	{
		Player(board);
		ChessBoard(board);
		if (Check(board))
		{
			return 0;
		}
		Computer(board);
		ChessBoard(board);
		if (Check(board))
		{
			return 0;
		}

	}
}

void Player(char board[LINE][LIST])
{
	int x = 0, y = 0;
	printf("玩家玩\n请输入坐标>:");
	while ((x < 1 || x > 3) || (x < 1 && x > 3))
	{
		scanf("%d%d", &x, &y);
		printf("\n");
		if ((x >= 1 && x <= 3) && (x >= 1 && x <= 3) && (board[x - 1][y - 1] == ' '))
		{
			board[x - 1][y - 1] = 'X';
			break;
		}
	}
}

void Computer(char board[LINE][LIST])  
{
	int x = 0, y = 0;
	int m = 1;
	printf("电脑玩\n");
	while (m)
	{
		x = rand()% 3;
		y = rand()% 3;
		
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			m = 0;
		}
	}
}

int Check(char board[LINE][LIST])   //When you pass an array, you must add the brackets in the back of the array.
{
	int i = 0,j = 0,flag = 0;
	for (i = 0; i <= 2; i++)
	{
		if (((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] == 'X')) || ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] == 'X')))
		{
			printf("The player wins the game！！！\n\n");
			return 1;
		}
		if (((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] == '#')) || ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] == '#')))
		{
			printf("The computer wins the game！！！\n\n");
			return 1;
		}
		if (((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] == 'X')) || ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] == 'X')))
		{
			printf("The player wins the game！！！\n\n");
			return 1;
		}
		if (((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] == '#')) || ((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] == '#')))
		{
			printf("The computer wins the game！！！\n\n");
			return 1;
		}
		for (j = 0; j <= 2; j++)  //平局
		{
			if (' ' != board[i][j])
			{
				flag++;
			}
			
		}
		if (9 == flag)
		{
			printf("平局\n");
			return 1;
		}
	}
	
	return 0;
}

