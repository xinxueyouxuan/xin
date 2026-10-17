#include <iostream>
using namespace std;

//引用做函数的返回值

	//不要返回局部变量的引用
int& aaa0(){
//int后面加上&，表示引用 
	int a = 10;
	//存放在栈区
	return a; 
} 

	//函数的调用可以作为左值 
int& aaa1(){
	static int a = 10;
	//静态变量，存放在全局区，该数据在程序结束后由系统释放 
	return a; 
} 

int main(){
	int &ref = aaa0();
	
	cout<<"ref = "<<ref<<endl;
	//第一次可以打印正确的,是因为编译器做了保留
	cout<<"ref = "<<ref<<endl; 
	//第二次打印出错，是因为a的内存已被释放 
	cout<<endl;
	
	int &ref2 = aaa1();
	
	cout<<"ref2 = "<<ref2<<endl; 
	cout<<"ref2 = "<<ref2<<endl;

	aaa1() = 1000;
	
	cout<<"ref2 = "<<ref2<<endl;
	cout<<"ref2 = "<<ref2<<endl;
	
	cin.get();
	return 0;
} 
