#pragma once
#define Row 12
#define Col 12
#define MineNum 10
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
void PrintMineClear(char arr[][Col],char arr1[][Col-2]);
void SetMine(char arr[][Col])
{
	int x = rand()%Row;
	int y = rand()%Col;

	while((x == 0) || (y == 0) || (x == Row-1) || (y == Col-1) || (arr[x][y] == '1'))
	{
		x = rand()%Row;
		y = rand()%Col;
	}
	if(arr[x][y] == '*')
		arr[x][y] = '1';
}

void InitMineClear(char arr[][Col])
{
	memset(arr,'*',sizeof(char)*Row*Col);
}

char CheckMineNear(char arr[][Col],int row,int x,int y)
{
	int i = 0;
	int j = 0;
	char count = '0';
	for(i = x-1; i <= x+1; i++)
	{
		for(j = y-1;j <= y+1; j++)
		{
			if(arr[i][j] == '1')
			{
				count+=1;
			}
		}
	}
	arr[x][y] = count;
	return arr[x][y];
}

int CheckMine(char arr[][Col],char arr1[][Col-2])
{
	int x = 0;
	int y = 0;
	int i = 0, j = 0;
	printf("ÇëÊäÈë×ø±ê:>\n");
	scanf("%d%d",&x,&y);
	if(arr[x][y] == '1')
	{
		printf("haha~~Äã±»Õ¨ËÀÀ²£¡\n");
		return 1;
	}
	arr[x][y] = CheckMineNear(arr,Row,x,y);
	i = x;
	j = y;
	if(arr[i][j] == '0')
	{
		int jIdx = j;
		int iIdx = i;
		while( --jIdx >= 1 )
		{
			arr1[iIdx][jIdx-1] = CheckMineNear(arr,Row,iIdx,jIdx-1);
			if(arr[iIdx][jIdx] != '0')
			{
				break;
			}
		}
		jIdx = j;
		iIdx = i;
		while(++jIdx <= 10)
		{
			arr1[iIdx-1][jIdx-1] = CheckMineNear(arr,Row,iIdx,jIdx+1);
			if(arr[iIdx][jIdx] != '0')
			{
				break;
			}
		}
		jIdx = j;
		iIdx = i;
		while(--iIdx >= 1)
		{
			arr1[iIdx-1][jIdx-1] = CheckMineNear(arr,Row,iIdx-1,jIdx);
			if(arr[iIdx][jIdx] != '0')
			{
				break;
			}
		}
		jIdx = j;
		iIdx = i;
		while(++iIdx <= 10)
		{
			arr1[iIdx-1][jIdx-1] = CheckMineNear(arr,Row,iIdx+1,jIdx);
			if(arr[iIdx][jIdx] != '0')
			{
				break;
			}
		}
	}
	PrintMineClear(arr,arr1);
}

void PrintMineClear(char arr[][Col],char arr1[][Col-2])
{
	int i = 0;
	int j = 0;
	for(i = 0; i < Col-1; i++)
	{
		printf(" %d ",i);
	}
	printf("\n----------------------------------\n");
	for(i = 1; i < Row-1;i++)
	{
		printf("%2d|",i);
		for(j = 1; j < Col-1; j++)
		{
			arr1[i-1][j-1] = arr[i][j];
			printf("%2c ",arr1[i-1][j-1]);
		}
		printf("\n");
	}
}

void Game()
{
	char arr1[Row][Col];
	char arr2[10][10];
	int count = MineNum;
	int i = 0;
	int j = 0;
	InitMineClear(arr1);

	while(count--)
		SetMine(arr1);
	for(i = 0; i < Row;i++)
	{
		for(j = 0; j < Col;j++)
		{
			if((arr1[i][j] == '*'))
			{
				arr1[i][j] == '0';
			}
		}
	}
	//PrintMineClear(arr1,arr2);
	if(CheckMine(arr1,arr2) == 1)
	{
		return;
	}
	PrintMineClear(arr1,arr2);
}