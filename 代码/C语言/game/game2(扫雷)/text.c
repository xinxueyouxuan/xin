#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu() {
	printf("****************************\n");
	printf("********   扫雷   **********\n");
	printf("********  1.play  **********\n");
	printf("********  0.exit  **********\n");
	printf("****************************\n");
}

void game() {
	char mine[ROWS][COLS] = { 0 };
	//存放布置好的雷的信息
	char show[ROWS][COLS] = { 0 };
	//存放排查出来的雷的信息

	//初始化数组的内容为指定的内容
	//mine数组在没有布置的时候，都是‘0’
	initboard(mine, ROWS, COLS, '0');
	//show数组在没有排查的时候，都是‘*’
	initboard(show, ROWS, COLS, '*');
	
	//设置雷
	setmine(mine, ROW, COL);
	displayboard(show, ROW, COL);
	//displayboard(mine, ROW, COL);

	//排查雷
	findmine(mine, show, ROW, COL);

}

int main() {
	//设置随机数的生成起点
	srand((unsigned int)time(NULL));
	int input = 0 ;
	do {
		menu();
		printf("请选择:>");
		scanf_s("%d", &input);
		switch (input) {
			case 1:
				printf("开始游戏！\n");
				game();
				break;

			case 0:
				printf("退出游戏！\n");
				break;
			
			default:
				printf("选择错误\n");
				break;
		}

	} while (input);
	return 0;
}