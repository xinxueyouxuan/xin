#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void initboard(char board[ROWS][COLS], int rows, int cols, char set) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = set;
        }
    }
}

void displayboard(char board[ROWS][COLS], int row, int col) {
    printf("\n------ 扫雷游戏 ------\n");
    // 打印列号（1~col）
    printf("   ");
    for (int j = 1; j <= col; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 1; i <= row; i++) {
        printf("%2d ", i);   // 行号，占2位对齐
        for (int j = 1; j <= col; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("---------------------\n");
}

void setmine(char board[ROWS][COLS], int row, int col) {
    int count = easy_count;
    while (count) {
        int x = rand() % row + 1;
        int y = rand() % col + 1;
        if (board[x][y] == '0') {
            board[x][y] = '1';
            count--;
        }
    }
}

// 统计(x,y)周围雷的个数
int get_mine_count(char mine[ROWS][COLS], int x, int y) {
    static int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    static int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (mine[nx][ny] == '1')
            count++;
    }
    return count;
}

// 递归展开周围无雷区域（经典扫雷的“自动翻开”功能）
void expand_blank(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y, int* win) {
    if (x < 1 || x > ROW || y < 1 || y > COL) return;  // 边界检查
    
    if (show[x][y] != '*') return;                     // 已翻开或已标记

    int cnt = get_mine_count(mine, x, y);
    if (cnt == 0) {
        show[x][y] = ' ';      // 空白区域显示空格
        (*win)++;
        // 递归展开周围8个格子
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                expand_blank(mine, show, x + dx, y + dy, win);
            }
        }
    }
    else {
        show[x][y] = cnt + '0';  // 显示数字
        (*win)++;
    }
}

void findmine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {
    int x, y;
    int win = 0;   // 已安全翻开格子数
    int total_safe = row * col - easy_count;

    while (win < total_safe) {

        displayboard(show, row, col);
        printf("请输入要排查的坐标 (行 列): ");
        
        if (scanf_s("%d %d", &x, &y) != 2) {
            
            // 输入错误（比如字母），清空缓冲区
            while (getchar() != '\n');
            printf("输入无效，请输入两个整数！\n");
            continue;
        }

        // 坐标合法性
        if (x < 1 || x > row || y < 1 || y > col) {
            printf("坐标超出范围，请重新输入 (1~%d)\n", row);
            continue;
        }

        if (show[x][y] != '*') {
            printf("该坐标已经排查过了，不能重复排查！\n");
            continue;
        }

        // 踩雷
        if (mine[x][y] == '1') {
            printf("\n 很遗憾，你被炸死了！ \n");
            displayboard(mine, row, col);
            break;
        }
        // 安全，展开
        else {
            expand_blank(mine, show, x, y, &win);
            // 每次展开后检查是否胜利
            if (win == total_safe) {
                printf("\n 恭喜你，成功排完所有雷！ \n");
                displayboard(mine, row, col);
                break;
            }
        }
        // 可选：清屏提升体验 (Windows)
        // system("cls");
    }
}