#include <iostream>
using namespace std;

int main(){
	int arr[5];
	//数组名arr是常量，不可以进行赋值等等操作 
	cout<<"存放arr[5]的地址在(默认16进制)"<<arr<<endl;
	cout<<"arr[0]的地址在"<<&arr[0]<<endl;
	cout<<"arr[5]中每个元素所占的内存为"<<sizeof(arr[0])<<endl;
	cout<<"数组arr[5]的内存大小为(sizeof(arr))"<<
	endl<<sizeof(arr)<<endl; 
	cout<<"数组arr[5]中元素个数为"<<sizeof(arr)/sizeof(arr[0])<<endl; 
	
	cin.get();
	return 0;
} 
