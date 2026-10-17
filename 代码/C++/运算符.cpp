#include <iostream>
using namespace std;

int main(){
	int a1 = 11,a2 = 2;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<endl;
	cout<<"算数运算符"<<endl;
	cout<<"a1+a2="<<a1+a2<<endl;
	cout<<endl;
	cout<<"a1-a2="<<a1-a2<<endl;
	cout<<endl;
	cout<<"a1*a2="<<a1*a2<<endl;
	cout<<endl;
	cout<<"a1/a2="<<a1/a2<<endl;
	cout<<endl;
	cout<<"a1%a2="<<a1%a2<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	cout<<"a1++="<<a1++<<endl;
	cout<<"a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a2="<<a2<<endl;
	cout<<"++a2="<<++a2<<endl;
	cout<<"a2="<<a2<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	cout<<"a1--="<<a1--<<endl;
	cout<<"a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a2="<<a2<<endl;
	cout<<"--a2="<<--a2<<endl;
	cout<<"a2="<<a2<<endl;
	cout<<endl;
	
	cout<<"复合运算符"<<endl; 
	cout<<"a1="<<a1<<endl;
	a1 += 2;
	cout<<"a1+=2后a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	a1 -= 1;
	cout<<"a1-=1后a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	a1 *= 4;
	cout<<"a1*=4后a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	a1 /= 2;
	cout<<"a1/=2后a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"a1="<<a1<<endl;
	a1 %= 3;
	cout<<"a1%=3后a1="<<a1<<endl;
	cout<<endl;
	
	cout<<"比较运算符"<<endl;
	a1 = 10,a2 = 11;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"输出1为真\n输出0为假"<<endl;
	cout<<"/a1==a1/ = "<<(a1==a2)<<endl;
	cout<<"/a1!=a1/ = "<<(a1!=a2)<<endl;
	cout<<"/a1>a1/ = "<<(a1>a2)<<endl;
	cout<<"/a1<a1/ = "<<(a1<a2)<<endl;
	cout<<"/a1>=a1/ = "<<(a1>=a2)<<endl; 
	cout<<"/a1<=a1/ = "<<(a1<=a2)<<endl;
	cout<<endl; 
	
	cout<<"逻辑运算符"<<endl;
	a1 = 12,a2 = 0;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"输出1为真\n输出0为假"<<endl;
	cout<<"!a1="<<!a1<<endl;
	cout<<"!!a1="<<!!a1<<endl;
	
	cout<<endl;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"a1&&a2="<<(a1&&a2)<<endl;
	a1 = 10,a2 = 11;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"(只要都不为0)a1&&a2="<<(a1&&a2)<<endl;
	cout<<"&&-->同真为真,其余为假"<<endl;
	
	cout<<endl; 
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"a1||a2="<<(a1||a2)<<endl;
	a1 = 0,a2 = 0;
	cout<<"a1="<<a1<<"\ta2="<<a2<<endl;
	cout<<"(只有两个都为0)a1||a2="<<(a1||a2)<<endl;
	cout<<"||-->同假为假,其余为真"<<endl;
	
	system("pause"); //cin.get();
	return 0;
} 
