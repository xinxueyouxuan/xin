#include<stdio.h>
void f(int *p);
void g(int k); 

int main(void){
	int i=6;
	int*  p=&i;//&i表示i的地址 
//*p后面一定要接一个变量，否则后续难以操作！！！ 
//	int*  p,q;//p是指针，而q只是一个变量； 
//	int  *p,q;//p是指针，而q只是一个变量；
	printf("&i=%p\n",&i);
	f(&i);//一定要有取址符&！！！
	g(i);
	return 0; 
}

void f(int *p){
	printf("p=%p\n",p);
	printf("*p=%d\n",*p);
	*p=26;//改变了i的值！！！
	//通过i的地址修改i的值！！！ 
}
void g(int k){
	printf("k=%d\n",k);
}
