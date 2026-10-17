#include <iostream>
using namespace std;

//常量定义：
//#define 定义 		宏常量 
//const 修饰的变量 	局部常量 

#define day 7
 
int main(){
	//1.define 
	//day = 14;
	//会报错，day是常量，不能修改！！！ 
	cout<<"一周一共有："<<day<<"天"<<endl;
	
	//2.const
	
	const int month = 12 ;
	//month = 24 ;
	//会报错，month是常量，不能修改！！！ 
	cout<<"一年一共有："<<month<<"月"<<endl;
	 
	system("pause");
	return 0;
} 
