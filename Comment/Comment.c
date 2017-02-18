#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"Comment.h"

enum STATE state = NUL_STATE;

void DoComment(FILE* pfIn, FILE* pfOut)
{
	while (state != END_STATE)
	{
		switch (state)
		{
		case NUL_STATE:
			DoNulState(pfIn, pfOut);
			break;
		case C_STATE:
			DoCState(pfIn,pfOut);
			break;
		case CPP_STATE:
			DoCppState(pfIn,pfOut);
			break;
		default:printf("注释转换完成\n");
		}
	}
}

void DoNulState(FILE* pfIn, FILE* pfOut)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '/':{
				 fputc('/',pfOut);
				 int scend = fgetc(pfIn);
				 if (scend == '/')
				 {
					 fputc('/', pfOut);
					 state = CPP_STATE;
				 }
				 else if (scend == '*')
				 {
					 fputc('/', pfOut);
					 state = C_STATE;
				 }
				 else
				 {  //这里面出现的是/dsfas的这种形式
				 }
	}
		break;
	case EOF:state = END_STATE;
		break;
	default:fputc(first, pfOut);
	}
}

void DoCppState(FILE* pfIn, FILE* pfOut)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '\n':{
				  state = NUL_STATE;
				  fputc('\n', pfOut);
	}
		break;
	case EOF:state = END_STATE;
		break;
	default:fputc(first, pfOut);
	}
}

void DoCState(FILE* pfIn, FILE* pfOut)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '*':
	{
				int scend = fgetc(pfIn);
				if (scend == '/')
				{
					//fputc('\n', pfOut);
					int thirth = fgetc(pfIn);
					if (thirth == '\n')
						fputc('\n', pfOut);
					else if (thirth == '/')
					{
						fputc('\n', pfOut);
						ungetc(thirth, pfIn);
						//还原到读取流中
						//处理   /**//**/
					}
					else
					{
						fputc('\n', pfOut);
						fputc(thirth, pfOut);
					}
					state = NUL_STATE;
				}

				else if (scend == '*')
				{
					fputc('*', pfOut);
					ungetc(scend, pfIn);
					state = C_STATE;
					//处理   /***/防止接下来如果有空行会出行多行的//
				}
				
				else
				{
					fputc('*', pfOut);
					fputc(scend, pfOut);
				}
	}
		break;
	case '\n':{
				  fputc('\n', pfOut);
				  fputc('/', pfOut);
				  fputc('/', pfOut);
	}
		break;
	case EOF:state = END_STATE;
		break;
	default:fputc(first, pfOut);
	}
}