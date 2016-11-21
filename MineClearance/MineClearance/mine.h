#ifndef __MINE_H__
#define __MINE_H__

#define LINE 10
#define LIST 10

int game(char UserBoard[LINE+2][LIST+2], char PlayerBoard[LINE][LIST]);
void PrintBoard(char Playerboard[LINE][LIST]);
void MineLay(char UserBoard[LINE + 2][LIST + 2]);
void PrintUser(char UserBoard[LINE + 2][LIST + 2]);
int MineClear(char UserBoard[LINE + 2][LIST + 2], char PlayerBoard[LINE][LIST]);

#endif   //mine.h