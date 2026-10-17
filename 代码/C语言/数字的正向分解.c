#include<stdio.h>
int main(){
	int x;
	scanf("%d",&x);
	int t=x,n=1;
	while(t>9){//t>9意为当t为两位数时
	      t /= 10;
		  n *= 10; 
	}//等价于用con计算数字有多少位，接着用pow(a,10)计算n！！！ 
	printf("x=%d,n=%d\n",x,n);
	do{
		int a = x / n;
		printf("%d", a);
		if( n > 9 ){
			printf(" ");
		}
		x %= n;
		n /= 10;
	}while( n > 0 );
	 printf("\n");
	return 0;
}
