#include <iostream>
#include <cstring> 
using namespace std;

struct student{
	string name;
	int age;
	int score;
};

void print(const student *p){
//防止函数修改结构体*p(main函数中结构体s)的值 

	//p->age = 100;操作失败,因为有const修饰 
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
	
	print(&s);	
	
	cin.get();
	return 0;
} 
