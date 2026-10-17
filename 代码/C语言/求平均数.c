#include<stdio.h>
int main(){
	double number;
	double sum=0;
	int count=0;
	
	scanf("%lf",&number);
	while(number!=-1){
		sum+=number;
		count++;
		scanf("%lf",&number);
	}
	printf("%f",sum/count);
	
	return 0;
} 
