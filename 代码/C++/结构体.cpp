#include <iostream>
#include <string>
using namespace std;

//struct --> 表示是结构体 
//定义结构体时struct不可以省略 
struct student{//成员列表 
	string name;
	int age;
	int chinese;
	int math;
	int english;
	int sum_score()const{
		return	chinese + math + english;}
}s3;//顺便创建s3 

int main(){
	//C++中'创建'结构体变量时,结构体关键字(struct)可以省略 
	student s1;
	//通过" ."访问结构体变量中的属性 
	s1.name = "张三";
	s1.age = 16;
	s1.chinese = 90;
	s1.math = 94;
	s1.english = 87;
	cout<<"姓名："<<s1.name<<"\n年龄："<<s1.age<<"\n总分："<<s1.sum_score()<<endl;
	cout<<endl;
	
	//struct student s2 ={ "李四", 18, 84, 100, 95 };
	//cout<<"姓名："<<s2.name<<"\n年龄："<<s2.age<<"\n总分："<<s2.sum_score<<endl;
	//当前编译器不允许这样赋值 
	cout<<endl;
	
	s3.name= "王五";
	s3.age=20;
	s3.chinese=97;
	s3.math=98;
	s3.english=95;
	cout<<"姓名："<<s3.name<<"\n年龄："<<s3.age<<"\n总分："<<s3.sum_score()<<endl;
	
	cin.get();
	return 0;
} 
