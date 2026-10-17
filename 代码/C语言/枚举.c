#include <stdio.h>

typedef enum weekday{
	mon ,tue ,wed ,thu ,fri ,sat ,sun
	//若mon不赋值,则默认mon=0,tue=1... 
}weekday;

int main(){
	//定义枚举数a 
	enum weekday a;
	//把mon的值赋给a 
	a = mon;
	weekday b;
	b = tue;
	printf("a=%d\n",a);
	printf("b=%d\n",b);
}
