#ifndef __CHESS_H__
#define __CHESS_H__

#define LINE 3
#define LIST 3

int game(char board[LINE][LIST]);
void Player(char board[LINE][LIST]);
void Computer(char board[LINE][LIST]);
void ChessBoard(char board[LINE][LIST]);
int Check(char board[LINE][LIST]);
//void ChessBoard(int LINE,int LIST );       �������󣬲�����ֱ���ú���Ϊ����,ͷ�ļ��в���������д��LIST��LINE������Ϊʵ�Σ���������Ϊ�β�
#endif  //__CHESS_H__