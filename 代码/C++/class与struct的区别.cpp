#include <iostream>
using namespace std;

class C1{
	int A;
	//默认私有权限-->private
}; 

struct C2{
	int A;
	//默认公共权限-->public 
};

int main(){
	
	C1 c1;
	//c1.A=100;
	//不可行,没有权限 
	
	C2 c2;
	c2.A=100;
	
	cin.get();
	return 0;
} 
