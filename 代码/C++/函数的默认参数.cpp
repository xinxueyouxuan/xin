#include <iostream>
using namespace std;

//函数的默认参数 
int  func0(int a,int b,int c){
	return a+b+c;
}
//如果我们自己传入数据，就用自己的数据，没有就用默认值
//语法：返回值类型+函数名（形参=默认值）{   } 
int func1(int a,int b=20,int c=30){
	return a+b+c;
}
//注：
//如果某个位置已经有了默认参数,那么从此位置往后,从左到右都"必须"有默认值 
	//int aaa0(int a=10,int b,int c){
	//	return a+b+c;
	//} 不行，会报错b,c都应为默认参数 
//如果函数的声明有默认参数，函数实现就不能有默认参数
	int aaa1(int a=10,int b=10);
	int aaa1(int a=10,int b=10){
		return a+b;
	} 

int main(){
	
	cout<<func0(10,20,30)<<endl<<endl;
	//不能少传 
	
	cout<<func1(10)<<endl<<endl;
	
	cout<<func1(10,30)<<endl;
	
	cin.get();
	return 0;
} 
