#include<stdio.h>
int main(){
	double m,h,a;
	scanf("%lf %lf",&m,&h);
	a=m/(h*h);
	
	if(a<18.5){
		printf("Underweight");
	}else if(a>=18.5&&a<24){
		printf("Normal");
	}else if(a>=24){
		printf("%.6g\nOverweight",a);
	}
	return 0;
} 
