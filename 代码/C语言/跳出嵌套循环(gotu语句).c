#include<stdio.h>
int main(){
	int x;
	int one,two,five;
	int exit=0;
	scanf("%d",&x);
	for(one=1;one<x*10;one++){
		for(two=1;two<x*10/2;two++){
			for(five=1;five<x*10/5;five++){
				if(one+two*2+five*5==x*10){
					printf("可以用%d个一角%d个两角%d个五角得到%d元\n",one,two,five,x);
					exit=1;
					goto a;//goto后面接一个自己设定的标号 
				}
			}
		}
	}
a://goto跳到这个标号的地方，并向下运行
//标号后面接冒号：！！！ 
	return 0;
} 
