//引用做函数参数 
//作用:函数传参时，可以利用引用的技术让形参修饰实参 
//优点: 可以简化指针修改实参 
#include <iostream>
using namespace std;

//值传递 
void aaa1(int a,int b){
	int temp = a;
	a = b;
	b = temp;
} 
//地址传递
void aaa2(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp; 
} 
//引用传递
void aaa3(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
} 
int main(){
	int a=10;
	int b=20;
	
	aaa1(a,b);
	
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	cout<<endl;
	
	aaa2(&a,&b);
	
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	cout<<endl;
	
	aaa3(a,b);
	
	cout<<"a="<<a<<endl;
	cout<<"b="<<b<<endl;
	
	cin.get();
	return 0;
} 
