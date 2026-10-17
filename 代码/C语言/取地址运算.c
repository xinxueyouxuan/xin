#include<stdio.h>
int main(void){
	int a,i,p;
	int x,y;
	int m[10];
	printf("a%x\n",a);
	printf("&a%x\n",&a);//&a表示a的地址！！！
	//即&取址符！！！ 
	printf("sizeof(a)%x\n",sizeof(a));
	printf("sizeof(&a)%x\n",sizeof(&a));
	printf("i%p\n",&i);
	printf("p%p\n",&p);
	printf("x%p\n",&x);
	printf("y%p\n",&y);
	printf("&m%p\n",&m);
	printf("m%p\n",m);
	printf("m[0]%p\n",m[0]);
	printf("m[1]%p\n",m[1]);
	printf("&m[0]%p\n",&m[0]);
	printf("&m[1]%p\n",&m[1]);
	return 0;
}
