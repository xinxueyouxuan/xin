#include<stdio.h>
int main(){
	int k,i,t;
	int s=0,sum=0;
	scanf("%d",&k);
	for(i=1;s<k;i++){
		s+=i;
		sum+=i*i;
	}s-=i-1;sum-=(i-1)*(i-1);
	t=k-s;
	sum+=t*(i-1);
	printf("%d",sum);
	return 0;
} 
