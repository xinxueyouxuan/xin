/*
题目描述 
新生报到那天，志愿者小蓝要从前门赶到图书馆，帮一位新生取寄存在那里的材料。
校园可以看成一个 n 行 m 列的方格：. 表示可以通行的道路，# 表示正在施工的楼栋（无法穿过），S 是小蓝的出发位置，E 是图书馆所在位置。小蓝每一步只能走到上、下、左、右四个方向相邻的一个可通行格子，走在路上不消耗额外时间。
请你算一算，小蓝最少要走多少步才能抵达图书馆；如果道路被施工楼栋完全阻断，则输出 −1。

输入描述:
第一行两个整数 n, m，用一个空格分隔。
接下来 n 行，每行一个长度为 m 的字符串，仅由字符 . # S E 组成。
输出描述:
输出一行一个整数，表示从 S 到 E 的最少步数；若无法抵达，输出 −1。

示例1
输入
3 3
S..
.#.
..E
输出
4
说明
一条最短路线是 (1,1) → (1,2) → (1,3) → (2,3) → (3,3)（行列号均从 1 开始），共走 4 步，绕开了中间那栋施工楼。

示例2
输入
3 3
S#.
##.
#.E
输出
-1
说明
起点右侧与正下方都被施工楼栋占据，小蓝一步也走不出去，因此输出−1。

备注:
3 ≤ n, m ≤ 1000。保证字符 S 与 E 各恰好出现一次，且它们所在的格子都不是 #。
*/
#include <stdio.h>
#include <string.h>

int main(void){
    int n,m,sum=0;
    scanf("%d %d",&n,&m);
    char arr[n][m];
    int starx,stary,finalx,finaly;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            scanf(" %c",&arr[i][j]);
            if(arr[i][j]=='S'){
                starx=i;
                stary=j;
            }
            else if(arr[i][j]=='E'){
                finalx=i;
                finaly=j;
            }
        }
    
    if(starx>finalx){
        if(stary>finaly){
            for(int i=starx;i>=finalx;i--){
                for(int j=stary;j>=finaly;j--){
                    if(arr[i][j]=='.'){
                        sum++;
                    }
                }
            }
        }
        else if(stary<finaly){
            for(int i=starx;i>=finalx;i--){
                for(int j=stary;j<=finaly;j++){
                    if(arr[i][j]=='.'){
                        sum++;
                    }
                }
            }
        }
        else if(stary==finaly){
            for(int i=starx;i>=finalx;i--){
                if(arr[i][stary]=='.'){
                    sum++;
                }
            }
        }
    }

    else if(starx<finalx){
        if(stary>finaly){
            for(int i=starx;i<=finalx;i++){
                for(int j=stary;j>=finaly;j--){
                    if(arr[i][j]=='.'){
                        sum++;
                    }
                }
            }
        }
        else if(stary<finaly){
            for(int i=starx;i<=finalx;i++){
                for(int j=stary;j<=finaly;j++){
                    if(arr[i][j]=='.'){
                        sum++;
                    }
                }
            }
        }
        else if(stary==finaly){
            for(int i=starx;i<=finalx;i++){
                if(arr[i][stary]=='.'){
                    sum++;
                }
            }
        }
    }
    else if(starx==finalx){
        if(stary>finaly){
            for(int j=stary;j>=finaly;j--){
                if(arr[starx][j]=='.'){
                    sum++;
                }
            }
        }
        else if(stary<finaly){
            for(int j=stary;j<=finaly;j++){
                if(arr[starx][j]=='.'){
                    sum++;
                }
                if(arr[starx][j]=='#'){
                    sum=-1;
                    break;
                }
            }
        }
    }
    else if(starx==finalx){
        if(stary>finaly){
            for(int j=stary;j>=finaly;j--){
                if(arr[starx][j]=='.'){
                    sum++;
                }
                if(arr[starx][j]=='#'){
                    sum=-1;
                    break;
                }
            }
        }
        else if(stary<finaly){
            for(int j=stary;j<=finaly;j++){
                if(arr[starx][j]=='.'){
                    sum++;
                }
                if(arr[starx][j]=='#'){
                    sum=-1;
                    break;
                }
            }
        }
        else if(stary==finaly){
            sum=0;
        }
    }

    printf("%d",sum);
    return 0;
}