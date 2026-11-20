#define _CRT_SECURE_NO_WARNINGS
#include"game.h"

menu() {
	printf("           下棋             \n");
	printf("\n");
	printf("****************************\n");
	printf("******** 1. play ***********\n");
	printf("******** 0. exit ***********\n");
	printf("****************************\n");

}
void game() {
	char board[ROW][COL] = {0};
	char ret;

	//初始化棋盘
	initboard( board , ROW , COL );
	Displayboard(board, ROW, COL);
	
	//开始下棋
	while (1) {
		playmove(board,ROW,COL);
		
		//判断输赢
		ret = iswin(board,ROW,COL);
		if(ret != 'C') {
			break;
		}

		Displayboard(board, ROW, COL);
		
		computermove(board,ROW,COL);
		
		//判断输赢
		iswin(board,ROW,COL);
		if (ret != 'C') {
			break;
		}

		Displayboard(board, ROW, COL);

	}
	if (ret == '*') {
		printf("玩家赢\n");
	}
	else if (ret == '#') {
		printf("电脑赢\n");
	}
	else {
		printf("平局\n");
	}

	Displayboard(board, ROW, COL);

}

int main() {
	srand((unsigned int)time(NULL));
	//设置随机数的生成起点
	int input = 0;
	do {
		//打印菜单
		menu();

		printf("请选择:>");
		scanf_s("%d",&input);

		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误\n");
			break;
		}

	} while (input);
	return 0;
}