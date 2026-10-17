#include <iostream>
using namespace std;

//全局变量
int ga=10;
int gb=10; 

//cg-->const (global)
const int cga=10;
const int cgb=10;

int main(){
	//局部变量
	int a=10;
	int b=10;
	
	cout<<"局部变量a的地址:"<<&a<<endl; 
	cout<<"局部变量b的地址:"<<&b<<endl; 
	cout<<endl;
	
	cout<<"全局变量ga的地址:"<<&ga<<endl; 
	cout<<"全局变量gb的地址:"<<&gb<<endl; 
	cout<<endl;
	
	//静态变量-->在数据类型之前 + static 
	static int sa=10;
	static int sb=10;
	
	cout<<"静态变量sa的地址:"<<&sa<<endl; 
	cout<<"静态变量sb的地址:"<<&sb<<endl; 
	cout<<endl; 
	 
	//动态变量-->在数据类型之前 + auto 
	auto int da=10;
	auto int db=10;
	
	cout<<"动态变量da的地址:"<<&da<<endl; 
	cout<<"动态变量db的地址:"<<&db<<endl; 
	cout<<endl;
	 
	//字符串常量 
	cout<<"字符串常量的地址为:"<<&"Hello World"<<endl;
	cout<<endl;
	
	//const修饰的变量 
	cout<<"const修饰的全局常量cga的地址:"<<&cga<<endl; 
	cout<<"const修饰的全局常量cgb的地址:"<<&cgb<<endl; 
	cout<<endl;
	
	//cl-->const (local)
	const int cla=10;
	const int clb=10;
	cout<<"const修饰的局部常量cla的地址:"<<&cla<<endl; 
	cout<<"const修饰的局部常量clb的地址:"<<&clb<<endl; 
	cout<<endl; 
	 
	cout<<"局部变量/动态变量/局部常量都在局部区"<<endl; 
	cout<<"全局变量/全局常量/静态变量/字符串常量都在全局区"<<endl; 
	
	cin.get();
	return 0;
} 
