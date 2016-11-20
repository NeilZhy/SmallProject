#ifndef __CHESS_H__
#define __CHESS_H__

#define LINE 3
#define LIST 3

int game(char board[LINE][LIST]);
void Player(char board[LINE][LIST]);
void Computer(char board[LINE][LIST]);
void ChessBoard(char board[LINE][LIST]);
int Check(char board[LINE][LIST]);
//void ChessBoard(int LINE,int LIST );       此语句错误，不可以直接用宏作为参数,头文件中不可以这样写，LIST和LINE可以作为实参，不可以作为形参
#endif  //__CHESS_H__