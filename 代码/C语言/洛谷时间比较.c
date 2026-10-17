#include<stdio.h>
int main(){
	int n,t1,t2;
	scanf("%d",&n);
	t1=5*n;
	t2=3*n+11;
	if(t1<=t2){
		printf("Local");
	}else{
		printf("Luogu");
	}
	return 0;
} 
