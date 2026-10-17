#include <iostream>
using namespace std;

int main(){
	short a1 = 10 ; 
	cout<< "a1= "<<a1<<endl;
	cout<< "short类型所占用的内存空间为：" << sizeof(a1) <<endl;
	
	int a2 = 11 ;
	int aa2[5] = {3,4,5,6,7};
	cout<<"数组aa2[0]= "<<aa2[0]<<endl;
	cout<< "a2= "<<a2<<endl;
	cout<< "int类型所占用的内存空间为：" << sizeof(a2) <<endl;
	
	long a3 = 12 ;
	cout<< "a3= "<<a3<<endl;
	cout<< "long类型所占用的内存空间为：" << sizeof(a3) <<endl;
	
	long long a4 = 13 ;
	cout<< "a4= "<<a4<<endl;
	cout<< "long long类型所占用的内存空间为：" << sizeof(a4) <<endl;
	
	float a5 = 10.1f ;
	float a55 = 3e5;
	float a555 = 3e-2;
	cout<< "a5= "<<a5<<endl;
	cout<< "a55= "<<a55<<endl;
	cout<< "a555= "<<a555<<endl;
	cout<< "float类型所占用的内存空间为：" << sizeof(a5) <<endl;
	
	double a6 = 10.2 ;
	cout<< "a6= "<<a6<<endl;
	cout<< "double类型所占用的内存空间为：" << sizeof(a6) <<endl;
	
	char a7 = 'A' ;
	char aa7[4] = "abc" ;
	cout<< "字符串aa7[4]= "<<aa7<<endl;
	cout<< "a7= "<<a7<<endl;
	cout<< "char类型所占用的内存空间为：" << sizeof(a7) <<endl;
	
	system("pause");
	return 0;
} 
