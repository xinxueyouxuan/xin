#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ROW 3
#define COL 3

//初始化棋盘
void initboard(char board[ROW][COL], int row, int col);

//打印棋盘
void Displayboard(char board[ROW][COL], int row, int col);

//玩家下棋
void playmove(char board[ROW][COL], int row, int col);

//电脑下棋
//找空白的位置随机下棋
void computermove(char board[ROW][COL], int row, int col);

//玩家赢 ->'*'
//电脑赢 ->'#'
//平局   ->'Q'
//继续   ->'C'
char iswin(char board[ROW][COL], int row, int col);