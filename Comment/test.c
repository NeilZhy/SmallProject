#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"Comment.h"



void test()
{
	FILE *pfIn = fopen("input.c","r");
	if (NULL == pfIn)
	{
		perror("input error\n");
		exit( EXIT_FAILURE );
	}
	FILE *pfOut = fopen("output.c", "a");
	if (NULL == pfOut)
	{
		perror("output error");
		exit(EXIT_FAILURE);
		fclose(pfIn);
	}

	DoComment(pfIn,pfOut);


	fclose(pfIn);
	fclose(pfOut);
}

int main()
{
	test();
	system("pause");
	return 0;
}