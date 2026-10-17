#include<stdio.h>
int main(){
	int n;
	int a=1;
	int i=1;
	//i的定义和表达式并不一定！！！ 
	scanf("%d",&n);
	for(i=1;i<=n;i++){
	//第一个表达式i=1是初始动作
	//第二个表达式i<=n是循环条件
	//第三个表达式i++是每次循环都要执行的指令 
		a*=i;
	}
	printf("%d!=%d",n,a);
	return 0;
} 
