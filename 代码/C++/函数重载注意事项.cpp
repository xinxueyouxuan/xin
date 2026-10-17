#include <iostream>
using namespace std;

//函数重载注意事项
	//引用作为重载条件 
void func(int &a){
	cout<<"func(int &a)"<<endl;
} 

void func(const int &a){
	cout<<"func(const int &a)"<<endl;
}
	//函数重载遇到默认参数
void func1(int a){
	cout<<"func1(int a)"<<endl;
}

void func1(int a,int b = 10){
	cout<<"func1(int a,int b=10)"<<endl;
}

int main(){
	
	int a = 10;
	
	func(a); 
	//因为a是变量，const修饰不了
	//即const int &a = a不合法 
	cout<<endl;
	
	func(10);
	//引用不能使用常数,即int &a = 10不合法 
	//但const int &a = 10合法 
	cout<<endl;
	
	func1(10,1);
	//但函数重载 遇到默认参数,会出现二义性,会报错,尽量避免 
	//传入一个值会报错 
	
	cin.get();
	return 0;
} 
