#include<stdio.h>
int main(){
	int k;
	int n=1; 
	double s=0.0;
	scanf("%d",&k);
	while(s<=k){
		s+=1.0/n;
		n++;
	} 
	printf("%d",n-1);
	return 0;
}
