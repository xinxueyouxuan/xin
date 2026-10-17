#include <iostream>
#include <cstring>
using namespace std;

struct student{
	string name;
	int age;
	int score;
}; 
void print1(struct student a){
	//值传递中修改结构体a不会修改main函数中结构体s的值 
	//占用内存较大(要复制main函数中结构体s的所有值) 
	cout<<"print1函数(值传递)中打印(输出)结构体s"<<endl;
	cout<<"姓名:"<<a.name<<endl
		<<"年龄:"<<a.age<<endl
		<<"分数:"<<a.score<<endl<<endl;
}
void print2(student *p){
	//地址传递中修改结构体*p会修改main函数中结构体s的值
	//占用内存较小，只占用几个字节 
	cout<<"print2函数(地址传递)中打印(输出)结构体s"<<endl;
	cout<<"姓名:"<<p->name<<endl
		<<"年龄:"<<p->age<<endl
		<<"分数:"<<p->score<<endl<<endl;
}

int main(){
	student s={"xiaomin",20,87};
	
	cout<<"main函数中打印(输出)结构体s"<<endl;
	cout<<"姓名:"<<s.name<<endl
		<<"年龄:"<<s.age<<endl
		<<"分数:"<<s.score<<endl<<endl;
	
	print1(s);
	print2(&s);
	
	cin.get();
	return 0;
} 
