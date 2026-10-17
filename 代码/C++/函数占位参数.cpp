#include <iostream>
using namespace std;

//占位参数 
//目前占位参数用不到 
//占位参数可以有默认参数 
void func(int a,int = 10){
	cout<<"this is func"<<endl;
} 

int main(){
	
	func(10，10);
	//占位参数必须填补，并且两个参数必须相同 
	
	cin.get();
	return 0;
} 
