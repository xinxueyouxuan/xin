#include <iostream>
using namespace std;

int main(){
	int a = 10;
	//指针定义：数据类型 *指针变量名;
	int *p;
	p = &a;//等价于"*p=a" 
	
	//也可以写成"int *p=&a" 
	 
	cout<<"&a="<<&a<<endl;
	cout<<"p="<<p<<endl;
	
	//指针p前面加一个*号即"*p"代表解引用,找到指针指向的内存中的数据 
	cout<<"*p="<<*p<<endl; 
	cout<<endl;
	
	//32位操作系统下，指针占4个字节(不管是什么数据类型) 
	//64位操作系统下，指针占8个字节(不管是什么数据类型) 

	cout<<"sizeof(int *)="<<sizeof(int *)<<endl;
	cout<<"sizeof(long *)="<<sizeof(long *)<<endl;
	cout<<"sizeof(long long *)="<<sizeof(long long *)<<endl;
	cout<<"sizeof(float *)="<<sizeof(float *)<<endl;
	cout<<"sizeof(double *)="<<sizeof(double *)<<endl;
	cout<<"sizeof(char *)="<<sizeof(char *)<<endl;
	cout<<"sizeof(p)="<<sizeof(p)<<endl;
	cout<<endl;
	
	cout<<"sizeof(*p)="<<sizeof(*p)<<endl;
	cout<<"sizeof(a)="<<sizeof(a)<<endl;
	cout<<"sizeof(int)="<<sizeof(int)<<endl;
	
	cin.get();
	return 0;
} 
