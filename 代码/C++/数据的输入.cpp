#include <iostream>
using namespace std;

int main(){
	//cin -->输入;后面接“>> ” 
	cout << "请输入两个int类型" << endl;
	int a1,a2;
	cin >> a1 >> a2;
	cout << "a1= " << a1 <<"\ta2= " << a2 << endl;
	
	cout << "请输入两个double类型" << endl;
	double b1,b2;
	cin >> b1 >> b2;
	cout << "b1= " << b1 <<"\tb2= " << b2 << endl;
	
	cout << "请输入两个字符类型" << endl;
	char c1,c2;
	cin >> c1 >> c2;
	cout << "c1= " << c1 << "\tc2= " << c2 <<endl;
	
	cout << "请输入两个字符串类型" << endl;
	string d1,d2;
	cin >> d1 >> d2;
	cout << "d1= " << d1 << "\td2= " << d2 <<endl;
	
	cout << "请输入两个布尔类型(只有0或非零数字有效)" << endl;
	bool flag1,flag2;
	cin >> flag1 >> flag2;
	cout << "flag1= " << flag1 << "\tflag2= " << flag2 << endl;
	
	cin.get();//等价于system("pause");
	return 0;
}
