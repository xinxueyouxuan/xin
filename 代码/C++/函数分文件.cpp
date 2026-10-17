#include <iostream>
#include "函数分文件.h"
//调用"函数份文件.h"这个文件 
using namespace std;

//	void swap(int a,int b);
//	
//	void swap(int a,int b){
//		int temp = a;
//		a = b;
//		b = temp;
//		cout<<"a="<<a<<endl;
//		cout<<"b="<<b<<endl;
//	}

int main(){
	int a=10,b=20;
	swap(a,b);
	cin.get();
	return 0;
} 
