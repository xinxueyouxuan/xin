#include <iostream>
using namespace std;

//常量引用
	//主要用来修饰形参，防止误操作
	//在函数形参列表中，可以加const修饰形参，防止形参改变实参
	
void aaa(const int& v){
	v = 10;
	cout<<"v = "<<v<<endl;
} 
 
int main(){
	//int &ref = 10;
	//引用本身就必须需要一个合法的内存空间，因此不能这样定义

	const int &ref = 10;
	//加上const后,编译器将代码修改为
		//int temp(临时变量)=10;const int &ref=temp 	
	//ref = 20; 加入const后，变为只读，不可修改 
	cout<<"ref = "<<ref<<endl;
	cout<<endl;
	 
	int a = 100;
	
	aaa(a); 
	
	
	cin.get();
	return 0;
} 
