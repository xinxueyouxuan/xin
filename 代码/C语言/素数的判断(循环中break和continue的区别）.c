#include<stdio.h>
int main(){
	int x;
	scanf("%d",&x);
	int i;
	for(i=2;i<x;i++){
		if(x%i==0){
		break;
		//break是跳出循环 ！！！ 
		//但如果用continue则这一轮循环不做了，直接开始下一轮 ！！！ 
		}
	} if(i==x){printf("%d是素数",x);
	}else{printf("%d不是素数",x);
	}
	return 0;
} 
