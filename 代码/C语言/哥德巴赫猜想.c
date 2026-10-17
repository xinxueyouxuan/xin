#include<stdio.h>
int ss(int x){//判断是不是素数
    int i;
    if(x < 2)return 0;
    if(x == 2)return 1;
    if(x%2 == 0)return 0;
    for(i = 3; i < x;i += 2){
        if( x%i == 0)return 0;
    }
    return 1;
}

int gdbh(int x){//验证哥德巴赫猜想
    int i;
    for(i=2;i<=x/2;i++){
        if(ss(i)&&ss(x-i)){
            printf("%d=%d+%d\n",x,i,x-i);
        	break;}
    }
}
int main(void){
    int N;
    scanf("%d",&N);
    int i=0;
    for(i = 4;i <= N;i += 2){
        gdbh(i);
    }
    return 0;
}
