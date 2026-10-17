#define _CRT_SECURE_WARNINGS
#include"game.h"

void initboard(char board[ROW][COL], int row, int col) {
	int i = 0, j = 0;
	for (i = 0;i < ROW;i++) {
		for (j = 0;j < COL;j++) {
			board[i][j] = ' ';
		}
	}
}

//第一版代码
//void Displayboard(char board[ROW][COL], int row, int col) {
//	int i = 0;
//	for (i = 0;i < ROW;i++) {
//		//打印数据
//		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
//		//打印分割线
//		if(i<row-1)
//		printf("---|---|---\n");
//	}
//}

void Displayboard(char board[ROW][COL], int row, int col) {
	int i = 0;
	for (i = 0;i < ROW;i++) {
		//打印数据
		int j;
		for (j = 0;j < col;j++) {
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		//打印分割线
		if (i < row - 1) {
			int j = 0;
			for (j = 0;j < col;j++) {
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}

//玩家下棋
void playmove(char broad[ROW][COL], int row, int col) {
	int x = 0, y = 0;
	printf("玩家下棋：>\n");
	while (1) {
		printf("请输入坐标：>\n");
		scanf_s("%d %d", &x, &y);
		
		//坐标合法判断

		if (x >= 1 && x <= ROW && y >= 1 && y <= COL) {
			if (broad[x - 1][y - 1] == ' ') {
				broad[x - 1][y - 1] = '*';
				break;
			}
			else {
				printf("坐标被占用，不能下棋\n");
			}
		}
		else {
			printf("坐标不合法，请重新输入\n");
		}
	}
}

//电脑下棋
void computermove(char board[ROW][COL], int row, int col) {
	printf("电脑下棋：>\n");

	int x = 0, y = 0;
	x = rand() % ROW;
	y = rand() % COL;
	while (1) {
		if (board[x][y] == ' ') {
			board[x][y] = '#';
			break;
		}
	}
}

//判断棋盘是否填满
//满了返回1；不满返回0
int isfull(char board[ROW][COL], int row, int col) {
	int i = 0;
	int j = 0;
	for (i = 0;i < row;i++) {
		for (j = 0;j < col;j++) {
			if (board[i][j] == ' ' ) {
				return 0;
			}
		}
	}
	return 1;
}

//判断输赢
 //第一版
char iswin(char board[ROW][COL], int row, int col) {
	int i;
	//判断行
	for (i = 0;i < row;i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ') {
			return board[i][1];
		}
	}
	int j;
	//判断列
	for (j = 0;j < col;j++) {
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ') {
			return board[1][j];
		}
	}
	//判断对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ') {
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') {
		return board[1][1];
	}

	//没人赢，判断平局
	if (isfull(board, ROW, COL)) {
		return 'Q';
	}
	//否则游戏继续
	else return 'C';
}

//char iswin(char board[ROW][COL], int row, int col) {
//    int i, j;
//
//    // 判断行：任意一整行完全相同且不为空格
//    for (i = 0; i < row; i++) {
//        if (board[i][0] == ' ')
//            continue;
//        int win = 1;
//        for (j = 1; j < col; j++) {
//            if (board[i][j] != board[i][0]) {
//                win = 0;
//                break;
//            }
//        }
//        if (win)
//            return board[i][0];
//    }
//
//    // 判断列：任意一整列完全相同且不为空格
//    for (j = 0; j < col; j++) {
//        if (board[0][j] == ' ')
//            continue;
//        int win = 1;
//        for (i = 1; i < row; i++) {
//            if (board[i][j] != board[0][j]) {
//                win = 0;
//                break;
//            }
//        }
//        if (win)
//            return board[0][j];
//    }
//
//    // 判断对角线（仅在方阵时有效）
//    if (row == col) {
//        // 主对角线
//		if (board[0][0] != ' ') {
//			int win = 1;
//			for (i = 1; i < row; i++) {
//				if (board[i][i] != board[0][0]) {
//					win = 0;
//					break;
//				}
//			}
//			if (win)
//				return board[0][0];
//        }
//        // 副对角线
//        if (board[0][col - 1] != ' ') {
//            int win = 1;
//            for (i = 1; i < row; i++) {
//                if (board[i][col - 1 - i] != board[0][col - 1]) {
//                    win = 0;
//                    break;
//                }
//            }
//            if (win)
//                return board[0][col - 1];
//        }
//    }
//
//    // 没人赢，判断平局
//    if (isfull(board, row, col)) {
//        return 'Q';
//    }
//    // 否则游戏继续
//    return 'C';
//}