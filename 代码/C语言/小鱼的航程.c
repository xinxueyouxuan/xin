#include<stdio.h>
int main(void){
	int x,n,w,d,s;
	scanf("%d %d",&x,&n);
	w=n/7;d=n%7;
	if(x+d<=6){s=w*5*250+d*250;}
	else if(x+d==7||(x==7&&d<6))
	{s=w*5*250+(d-1)*250;}
	else{s=w*5*250+(d-2)*250;}
	printf("%d",s);
	//有点问题 
	return 0;
}
