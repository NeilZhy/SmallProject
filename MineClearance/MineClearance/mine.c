#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"mine.h"

void MineLay(char UserBoard[LINE + 2][LIST + 2])
{
	int x = 0, y = 0,i = 0;
	while (i < 20)
	{
		x = rand() % 10 + 1;
		y = rand() % 10 + 1;
		if ('0' == UserBoard[x][y])
		{
			UserBoard[x][y] = '1';
			i++;
		}
	}
}

void PrintBoard(char Playerboard[LINE][LIST])
{
	int i = 0, j = 0;
	printf("  0 1 2 3 4 5 6 7 8 9 10\n");
	printf("------------------------\n");
	for (i = 0; i < LINE; i++)
	{
		printf("%2d| ",i+1);
		for (j = 0; j < LIST; j++)
		{
			printf("%c ",Playerboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int MineClear(char UserBoard[LINE + 2][LIST + 2], char PlayerBoard[LINE][LIST])
{
	int x = 0, y = 0,num = 0,win = 0;
	while (1)
	{
		printf("ÇëÊäÈëÉ¨À××ø±ê>:");
		scanf("%d%d", &x, &y);
		if ((x > 0 && x <= 10) && (y > 0 && y <= 10))
		{
			if ('1' == UserBoard[x][y])
			{
				PlayerBoard[x-1][y-1] = '#';
				PrintBoard(PlayerBoard);
				printf("°¡£¡£¡£¡£¡Äã±»Õ¨ËÀÀ²£¡£¡£¡£¡\n");
				return 0;
			}
			if ('0' == UserBoard[x][y])
			{
				num = (UserBoard[x-1][y-1]-'0') + 
					(UserBoard[x-1][y] - '0') + 
					(UserBoard[x-1][y+1]-'0') + 
					(UserBoard[x][y - 1] - '0') + 
					(UserBoard[x][y+1] - '0') + 
					(UserBoard[x+1][y-1]-'0') + 
					(UserBoard[x+1][y] - '0') + 
					(UserBoard[x+1][y+1]-'0');
				PlayerBoard[x-1][y-1] = num + '0';
				PrintBoard(PlayerBoard);
			//	PrintUser(UserBoard);
				win++;
				if (win >= 80)
				{
					printf("É¨À×³É¹¦£¬ÄãÓ®ÁË£¡£¡£¡\n");
					return 0;
				}
			}
		}
	}
}

int game(char UserBoard[LINE+2][LIST+2], char PlayerBoard[LINE][LIST])
{
	int x = 0, y = 0;
	int i = 0, j = 0;
	PrintBoard(PlayerBoard);
	MineLay(UserBoard);
	//PrintUser(UserBoard);
   return  MineClear(UserBoard, PlayerBoard);
	return 0;
}

//void PrintUser(char UserBoard[LINE + 2][LIST + 2])
//{
//	int i = 0, j = 0;
//	printf(" 0 1 2 3 4 5 6 7 8 9 10\n");
//	for (i = 0; i < LINE + 2; i++)
//	{
//		printf("%2d ", i + 1);
//		for (j = 0; j < LIST + 2; j++)
//		{
//			printf("%c ", UserBoard[i][j]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}