#include<stdio.h>
#include<windows.h>
int main() {
	int i;
	for(i=1;i<1000;i++){
		printf("%d ", i );
		sleep(1);//sleep()括号里面的整数是秒，意为输出间隔多少秒！！！ 
		//Sleep()括号里的整数是毫秒！！！ 
	}
	return 0;
}
