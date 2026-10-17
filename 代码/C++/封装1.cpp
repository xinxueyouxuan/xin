#include <iostream>
#include <string>
using namespace std;

//C++面向对象的三大行为：封装、继承、多态
//C++认为万事万物皆为对象，对象上有其属性和行为
//具有相同属性的对象，我们可以抽象称为类，人属于人类，车属于车类

//封装：是C++面向对象的三大特征之一 
/*
  	意义:将属性和行为作为一个整体，表现生活中的事物
  		 将属性和行为加以权限控制
  		 
	一.在设计的时候，属性和行为写在一起，表现事物
	  语法:class 类名(访问权限: 属性 / 行为 )； 

*/ 

//设计一个圆类 
const double PI = 3.14;

class yuan//'yuan'就是这个类的名字 
{
	//访问权限
	public: 
	//公共权限 
	
	//属性和行为统称为 成员 
	//属性 成员属性 成员变量 
	//行为 成员函数 成员方法 
	int r; 
	
	//行为 
	//获取圆的周长
	double L(){
		return 2 * PI * r;
	} 
};

//设计一个学生类
class student{
	
	public:
	
	//属性 
	string name;
	int ID;
	
	//行为
	void show(){//显示 
		cout<<"姓名："<<name<<endl<<"学号："<<ID<<endl;
	} 
	
	void setname(string name1){
		name = name1;
	}
	
	void setID(int id){
		ID = id;
	}
}; 
int main(){
	
	//通过圆类 创建具体的圆（对象）
	yuan c1;
	
	//给圆对象 的属性进行赋值
	c1.r = 10;
	
	cout<<"圆的周长为:"<<c1.L()<<endl; 
	cout<<endl;
	
	//通过学生类 创建具体的学生（对象）
	student s1;
	//s1.name = "张三";
	s1.setname("张三");
	//s1.ID = 1;
	s1.setID(1);
	
	s1.show();
	cout<<endl; 
	
	student s2;
	s2.name = "李四";
	s2.ID = 2;
	
	s2.show();
	cout<<endl;
	
	cin.get();
	return 0;
} 
