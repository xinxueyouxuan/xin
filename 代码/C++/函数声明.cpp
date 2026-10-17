#include <iostream>
using namespace std;

int max(int a,int b);
int max(int a,int b);
int max(int a,int b);
//声明函数可以有多次 

int main(){
	int a=10,b=20;
	cout<<max(a,b)<<endl;
	
	cin.get();
	return 0;
} 

//函数定义只能有一次 
int max(int a,int b){
	return a>b ? a : b;
}
