#include <iostream>
using namespace std;

//函数的重载
	//函数可以重名(函数名可以相同),提高复用性
//条件：
	//函数都在同一个'作用域'下
	//函数名称相同
	//函数的'类型不同'/'个数不同'/'顺序不同'
//“函数的返回值不可以作为函数重载的条件”
 
void func(){
	cout<<"func()"<<endl;
}

void func(int a){
	cout<<"func(int)"<<endl;
} 

void func(double a){
	cout<<"func(double)"<<endl;
}

void func(int a,double b){
	cout<<"func(int double)"<<endl;
}

void func(double a,int b){
	cout<<"func(double int)"<<endl;
}
//注：
//函数的返回值'不可以'做为函数重载条件 
int func(double a,int b){
	cout<<"int func"<<endl;
}
int main(){
	
	func();
	cout<<endl; 
	
	func(10);
	cout<<endl;
	
	func(10.1);
	cout<<endl;
	
	func(10,10.1);
	cout<<endl;
	
	func(10.1,10);
	cout<<endl;
	
	cin.get();
	return 0;
} 
