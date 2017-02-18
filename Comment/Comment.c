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
		default:printf("ע��ת�����\n");
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
				 {  //��������ֵ���/dsfas��������ʽ
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
						//��ԭ����ȡ����
						//����   /**//**/
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
					//����   /***/��ֹ����������п��л���ж��е�//
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