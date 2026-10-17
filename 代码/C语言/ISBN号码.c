#include<stdio.h>
int main(){
	int a,b,c,d,e,f,g,h,i,x;
	char  n;
	scanf("%1d-%1d%1d%1d-%1d%1d%1d%1d%1d-%c",&a,&b,&c,&d,&e,&f,&g,&h,&i,&n);

	x=(1*a+2*b+3*c+4*d+5*e+6*f+7*g+8*h+9*i)%11;

	if((x==10&&n=='X')||(x!=10&&n-'0'==x))//n-'0'是字符转换为数字！！！ 
	{printf("Right");}
	
	else if(x==10){
	printf("%d-%d%d%d-%d%d%d%d%d-X",a,b,c,d,e,f,g,h,i);}
	else{printf("%d-%d%d%d-%d%d%d%d%d-%d",a,b,c,d,e,f,g,h,i,x);}
	
	return 0;
} 
