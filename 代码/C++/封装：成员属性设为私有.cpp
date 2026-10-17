#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//成员属性设置为私有
//可以自己控制读写权限
//对于写可以检测数据的有效性 
class Person
{
public:
	void setName(string name){
		Name = name; 
	}
	
	string getName(){
		return Name;
	}
	
	void setAge(int age){
		if(age<0||age>150){
			cout<<"输入有误"<<endl;
			return; 
		}
		Age = age;
	}
	
	int getAge(){
		return Age;
	} 
	
	void setIdol(string idol){
		Idol = idol;
	}
	
private: 
	string Name;
	//可读可写 
	
	int Age = 18 ;
	//只读 也可以写(0~150) 
	
	string Idol;
	//只写 
	 
}; 

int main(){
	
	Person p1;
	
	p1.setName("张三");
	cout<<"姓名："<< p1.getName()<<endl;
	cout<<endl;
	
	cout<<"年龄："<< p1.getAge()<<endl;
	cout<<endl;
	
	p1.setIdol("初音未来"); 
	
	p1.setAge(160);
	
	cin.get();
	return 0;
} 
