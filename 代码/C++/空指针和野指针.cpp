#include <iostream>
using namespace std;

int main(){
	//空指针:指针变量指向内存中编号为0的空间 
		//用途:初始化指针变量 
		//注意: 空指针的内存是不可以访问的 
	int *p1 = NULL;
	//*p = 100;不可访问;
	//0~255之间的内存编号是系统占用的,因此不可以访问 
	cout<<"空指针*p1="<<*p1<<endl; 
	//输出会崩 
	
	//野指针:指针变量指向非法的内存空间 
	int *p2 = (int *)0x1100;
	cout<<"野指针*p2="<<*p2<<endl; 
	//输出会崩 
	
	cin.get();
	return 0;
} 
