#include<stdio.h>
int main(){
    unsigned int m, t, s, y;
    //unsigned int是非负整数 
    int x;
    scanf("%u %u %u", &m, &t, &s);
    //%u表示输入非负整数 
    if(t == 0){
        printf("0");
    } else {
        y = (s+t-1) / t; 
		// 计算已吃苹果数
        x = m - y;
        printf("%d", x < 0 ? 0 : x);
        //x<0是条件，？后面是真、假命题
		//第一个0是满足条件时输出的结果
		//第二个x是不满足条件时输出的结果 
    }
    return 0;
}
