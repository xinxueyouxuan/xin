#include<stdio.h>
int main(void){
	int i=6,j;
	const int *p0=&i;//固定的是*p的值，但可以改变*p的地址 
//	*p0=9;不能这样修改！！！
	i=26;//可以修改i从而修改p 
	printf("*p0=%d\n",*p0);
	p0=&j;//可以改变p的地址从而改变p的值 
	j=9;
	printf("*p0=%d\n",*p0);
//	const *p相当于定义了一个常量 
	
	int a=2;
	int *const p1=&a;
//	p1=&j;不可以改变p1的地址
	printf("*p1=%d\n",*p1); 
	*p1=23;//可以直接修改p1的值！！！ 
	printf("*p1=%d\n",*p1);
//	*const p相当于定义了一个地址 
	
	return 0;
} 
