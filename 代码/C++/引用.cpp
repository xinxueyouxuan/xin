#include <iostream>
using namespace std;

//引用就是一个地址，两个变量
//数据类型 &别名 = 原名
//char a = 'd';
// char &b = a;
int main(){
	
	int a = 10;
	int &b = a; 
	
	cout<<"a="<<a<<endl<<"b="<<b<<endl;
	cout<<endl;
	
	b=100;
	//a,b都被修改
	
	cout<<"a="<<a<<endl<<"b="<<b<<endl; 
	cout<<endl;
	
	//int &z;//错误,引用必须初始化
	int x = 10;
	int y = 20;
	int &z = x;//一旦初始化后不可更改
	
	cout<<"x="<<x<<endl;
	cout<<"y="<<y<<endl;
	cout<<"z="<<z<<endl;
	cout<<endl; 
	
	z = y;//这时赋值,不是更改引用
	
	cout<<"x="<<x<<endl;
	cout<<"y="<<y<<endl;
	cout<<"z="<<z<<endl;
	
	cin.get();
	return 0;
} 
