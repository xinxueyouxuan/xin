#include <iostream>
using namespace std;

int main(){
	int i,array[10] = {10,20,30,40,50
	,60,70,80};//array-->意为数组 
/*
		1.定义数组-->数组类型 + 数组名 + [数组长度]
		2.数组存放在一块连续的内存空间中
		3.每一个元素都是相同数据类型
*/
	for(i=0;i<10;i++)
		cout<<array[i]<<endl;
	
	cin.get();
	return 0;
} 
