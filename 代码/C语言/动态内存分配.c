#include<stdio.h>
#include<stdlib.h>

int main(void){
	int number;
	int *a;
	int i;
	scanf("%d",&number);
	a = (int *)malloc(number*sizeof(int));
	//malloc->申请一块空间 
	for (i=0 ;i<number ;i++ ){
		scanf("%d",&a[i]);
	}
	for(i=number-1 ;i>=0 ;i-- ){
		printf("a[%d] = %d\n",i,a[i]);
	}
	free(a);//归还所申请的空间（a是没有修改地址之前的） 
	//free后的括号里面不能接地址改变过后的a
	//尽量有malloc就对上一个free（）！！！ 
	
	return 0;
} 
