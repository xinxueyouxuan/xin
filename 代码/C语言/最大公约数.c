#include<stdio.h>
int main(){
	int a,b;
	int t;
	scanf("%d %d",&a,&b);
	
	while( b != 0){
		t = a % b;
		a = b;
		b = t;
		printf("a=%d,b=%d,t=%d",a,b,t);
	}//辗转相除法求最大公约数 
	printf("a,b的最大公约数是%d",a);
	return 0;
}
