#include<stdio.h>
int main(){
	int a=0;
	int x=0;
	int y=0;
	scanf("%d",&a);
	while(a>0){
		x=a%10;
    	y=y*10+x;
		printf("a=%d x=%d y=%d\n",a,x,y);
		a/=10;
	}
	printf("%d",y);//可以用来把12345颠倒成54321 
	return 0;
} 
