#include <iostream>
using namespace std;
	
	void swap(int a,int b){
		int temp = a;
		a = b;
		b = temp;
		cout<<"a="<<a<<endl;
		cout<<"b="<<b<<endl;
	}
//新建一个名叫"函数分文件.h"的头文件 
