#include<stdio.h>

int main()
{
	int h1,min1;
	int h2,min2;
	
	printf("请输入时间1和时间2\n");
	scanf("%d %d",&h1,&min1);
	scanf("%d %d",&h2,&min2);
	
	int h=h2-h1;
	int min=min2-min1;
	
	if(min<0)
	{
	min=min+60;
	h=h-1;	
	} 
	printf("时间差是%d小时%d分钟",h,min);
	return 0;
}
