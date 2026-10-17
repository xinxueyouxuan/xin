#include<stdio.h>

int main(){
	int s,v,t;
	scanf("%d %d",&s,&v);
	t=480-(s+v-1)/v-10;
	//(s+v-1)等价于s/v向上取整！！！ 
	if(t<0){
		t+=24*60;
	}
	int h=t/60;
	int min=t%60;
	printf("%02d:%02d",h,min);
	return 0;
} 
