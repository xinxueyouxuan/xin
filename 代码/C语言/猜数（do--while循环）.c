#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
	srand(time(0));
	//为了便于后面获取随机数 
	int count=0;
	int number=rand()%100+1;
	//每次召唤rand()就得到一个随机的整数 
	//%100+1是控制所取随机数的范围 
	int a=0;
	
	printf("我已经想好一个1到100之间的数。\n");
	
	do{printf("猜猜这个数：\n");
	scanf("%d",&a);
	count ++; 
	if(a>number){printf("你猜的数大了。");}
	else if(a<number){printf("你猜的数小了。");}	
	}while(a!=number);
	
	printf("你猜对了，一共猜了%d次",count);
	return 0;
} 
