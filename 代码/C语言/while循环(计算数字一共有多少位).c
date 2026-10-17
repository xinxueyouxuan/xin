#include<stdio.h>

int main(){
	
	int a;
	int n=0;
	
	printf("请输入数字\n");
	scanf("%d",&a);
	
	while(a>0)
	//while后面的括号()里是变量应该满足的条件 
	//只要满足该条件将一直执行while后面大括号{}内的指令 
	    {
		a/=10;
		n++;
	    }
	printf("该数一共有%d位\n",n); 
	//注意该代码不包括0！！！ 
	//计算机执行该指令时会受到限制，即最多只能计算出10位！！！ 
	
	return 0;
} 
