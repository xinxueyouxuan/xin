#include<stdio.h>

int idPrime(int i){//判断素数的函数 
	int ret = 1;
	int k;
	for ( k = 2; k<i-1;k++){
		if(i%k==0){
			ret = 0;
			break;}
			return 0; 
	}
}
//定义自己的函数！！！
int s(int begin,int end)
//int返回类型；s函数名；（）内是参数表，参数之间用，逗号分割！！！ 
{//计算区间和的函数 
	int i;
	int sum=0;
	for(i=begin;i<=end;i++){
		sum +=i;
	}
	printf("%d到%d的和是%d\n",begin,end,sum);
	return 0;}
int main(){
//	int m,n;
//	int sum=0,cnt=0;
//	int i;
//	scanf("%d %d",&m,&n);
//	if(m==1){
//		m=2;} 
//	for(i=m;i<=n;i++){
//		if(isPrime(i)){
//		sum +=i;
//		cnt++;}
//	}
//	printf("cnt=%d sum=%d\n",cnt,sum);

	s(20,30);
	
	return 0;
} 
