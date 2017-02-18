#ifndef __COMMENT_H__
#define __COMMENT_H__

#include<stdio.h>
#include<stdlib.h>

enum STATE
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};

void DoComment(FILE* pfIn, FILE* pfOut);
void DoNulState(FILE* pfIn, FILE* pfOut);
void DoCState(FILE* pfIn, FILE* pfOut);
void DoCppState(FILE* pfIn, FILE* pfOut);

#endif