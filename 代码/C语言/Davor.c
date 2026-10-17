#include<stdio.h>
int main(){
	int N,X,K,T;
	scanf("%d",&N);
//(7*X+21*K)*52=N;求maxX,minK 
	 T=N/364;
	for(K=1;K<=T/3;K++){
		X=T-3*K;
		if(X<=100&&X>0){
			printf("%d\n%d\n",X,K);
			break;
		} 
	}
	return 0;
}
