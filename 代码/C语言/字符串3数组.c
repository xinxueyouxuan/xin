#include<stdio.h>
int main(void){
	char a[3][10]=//每一个a[]只能容纳不超过9的字符
				  //(\0也要占一个，可以修改！！！) 
	{"hello","world","hi"};
	char *b[3]=//每一个b[]都可以容纳很多字符
			   //(但不可以修改！！！) 
	{"hello","world","hi"};
	int i;
	for(i=0;i<3;i++){
		printf("a[%d]=%s  *b[%d]=%s\n",i,a[i],i,b[i]);
	} 
	return 0;
}
