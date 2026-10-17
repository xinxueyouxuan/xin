#include <iostream>
using namespace std;

//栈区数据注意事项---不要返回局部变量的地址 
//栈区的数据由编译器管理开辟和释放 

int* func(int x)//形式参数(形参)也会放在栈区 
{
	int a=10;//局部变量 
	return &a;//返回局部变量的地址 
}
int main(){
	
	int *p = func(10);
	
	//cout<<"p="<<p<<endl; 
	cout<<"*p="<<*p<<endl;
	//第一次可以打印正确的,是因为编译器做了保留(不论是地址还是值) 
	cout<<"*p="<<*p<<endl;
	//第二次数据就不在被保留 
	
	cin.get();
	return 0;
} 
