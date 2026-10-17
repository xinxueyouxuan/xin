#include <iostream>
using namespace std;

//new的基本语法
int* func(){
	//在堆区创建整形数据
	//new返回的是 该数据类型的指针 
	int *p = new int(10);
	
	return p;
}
void text1(){
	int *p = func();
	
	cout<<"*p="<<*p<<endl;
	cout<<endl;
	//堆区的数据由管理员开辟、释放
	
	delete p;
	//释放堆区数据 
	cout<<"*p="<<*p<<endl;
	//该内存已被释放 
	cout<<endl; 
}
//在堆区利用new开辟数组 
void text2(){
	//创建一个在堆区的数组
	int *arr = new int[10]; 
	int i;
	for(i=0;i<10;i++){
		arr[i] = i + 10;
		//给十个元素赋值 
	}
	for(i=0;i<10;i++){
		cout<<"arr["<<i<<"]="<<arr[i]<<endl;
	}
} 
int main(){
	text1();
	
	text2();
	
	cin.get();
	return 0;
} 
