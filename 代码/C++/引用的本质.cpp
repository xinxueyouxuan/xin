#include <iostream>
using namespace std;

//引用的本质在C++内部实现是一个指针常量

void aaa0(int &ref){
	ref = 100;
	//因为ref是引用，所以可以转化为*ref = 100； 
} 

int main(){
	int a = 10;
	
	int &ref = a;
	//自动转化为 int* const ref = &a;
	//指针常量是指针指向不可改,即引用也是 
	
	cout<<"ref = "<<ref<<endl;
	cout<<"a = "<<a<<endl;
	cout<<endl; 
	
	ref = 20;
	//内部发现ref是引用，自动转化为*ref = 20; 
	
	cout<<"ref = "<<ref<<endl;
	cout<<"a = "<<a<<endl;
	cout<<endl;
	
	aaa0(a);
	
	cout<<"ref = "<<ref<<endl;
	cout<<"a = "<<a<<endl; 
	
	cin.get();
	return 0;
} 
