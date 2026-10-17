#include <iostream>
using namespace std;

int main(){
	//const修饰指针 ---常量指针 
		//指针指向可以修改，值不可以修改 
	int a=10,b=20;
	cout<<"a="<<a<<"\tb="<<b<<endl; 
	const int *p1=&a; 
	//*p = 11;不可行，不能修改 
	cout<<"*p1="<<*p1<<endl;
	p1 = &b;
	cout<<"*p1="<<*p1<<endl;
	cout<<endl;
	
	//const修饰常量 ---指针常量 
		//指针指向不可以改，值可以改 
	cout<<"a="<<a<<"\tb="<<b<<endl; 
	int *const p2=&a;
	cout<<"*p2="<<*p2<<endl;
	*p2= 11;
	cout<<"*p2="<<*p2<<endl;
	//*p2=&b;不可行 
	cout<<endl;
	
	a=10;
	//const即修饰指针，又修饰常量 
		//指针指向和值都不可以修改 
	cout<<"a="<<a<<"\tb="<<b<<endl;  
	const int *const p3=&a;
	cout<<"*p3="<<*p3<<endl;
	//*p3=11;不可行 
	//*p3=&b; 不可行 
	
	
	cin.get();
	return 0;
} 
