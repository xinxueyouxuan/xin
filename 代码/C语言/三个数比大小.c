#include<stdio.h>

int main(){
	double a,b,c;
	
	scanf("%lf %lf %lf",&a,&b,&c);
	
	double max=0;
	//else与最近的if相匹配 
	if(a>=b){
		if(a>=c){
			max=a;
		}
		else{
			max=c; 
		}
	}
	else{
		if(b>c){
			max=b;
		}
		else{
			max=c;
		}
	}
	printf("最大的是%f",max);
	return 0;
}
