#include<stdio.h>
#include<math.h>

int main(){
	int n;
	scanf("%d",&n);
	double a=sqrt(5);//sqrt是根号的意思 
	double b=(1+a)/2;
	double c=(1-a)/2;
	double Fn=(pow(b,n)-pow(c,n))/a;//pow(x,y)是x的y次方的意思 
	printf("%.2f",Fn);
	return 0;
} 
