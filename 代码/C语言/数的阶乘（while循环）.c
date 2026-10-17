#include<stdio.h>
int main(){
	int n;
	int a=1;
	int i=1;
	scanf("%d",&n);
	while(i<=n){
		a*=i;
		i++;
	}
	printf("%d!=%d",n,a);
	return 0;
}
