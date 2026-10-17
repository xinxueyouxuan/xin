#include<stdio.h>

int main(){
	
	int a;
	scanf("%d",&a);
	
	switch(a){
		//switch后面的括号()里面是一个变量
		 
		case 1:
		printf("早上好\n");
		break;
		//注意case后面是冒号：不是分号； 
		//当case为一时，一直执行到离case 1最近的break才停止
		
		case 2:
		printf("中午好\n");
		break;
		
		case 3:
		printf("晚上好\n");
		break;
		
		default:
		//default(默认，即以上case都不满足时执行)
		//default后面是冒号：不是分号；
		printf("我不好\n");
		break;
		//break后面不再执行下一步操作 
		printf("000");
	}
	return 0;
 } 
