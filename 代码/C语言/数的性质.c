#include<stdio.h>
int main(){
	int x,a,b,c,d;
	scanf("%d",&x);
	if(x%2==0)
	{if(x>=4&&x<=12)
	{a=1;b=1;c=0;d=0;}
     else{a=0;b=1;c=1;d=0;}
	}
	else{ if(x>=4&&x<=12)
	{a=0;b=1;c=1;d=0;}
	else{a=0;b=0;c=0;d=1;}
	}
	printf("%d %d %d %d",a,b,c,d);
	return 0;
} 
