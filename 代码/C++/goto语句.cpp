#include <iostream>
using namespace std;

int main(){
	cout << "1" << endl;
	cout << "2" << endl;
	
	goto flag;//跳到flag位置处 
	
	cout << "3" << endl;
	cout << "4" << endl;
	cout << "5" << endl;
	cout << "6" << endl;
	
	flag : //flag后面是冒号' : ' 
	
	cout << "7" << endl;
	cout << "8" << endl;
	cout << "9" << endl;
	cout << "10" << endl;
	cout << "11" << endl;
	
	cin.get();
	return 0;
}
