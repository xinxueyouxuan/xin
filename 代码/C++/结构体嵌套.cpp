#include <iostream>
#include <cstring>
using namespace std;

struct strudent{
	string name;
	int age;
	int score;
}; 
struct teacher{
	int id;
	string name;
	int age;
	struct strudent stu;
};

int main(){
	teacher t1={10086,"徐淑静",19,{"张三",12,60}};
	teacher t2;
	t2.id = 10087;
	t2.name = "老王";
	t2.age = 34;
	t2.stu.name = "李四";
	t2.stu.age = 18;
	t2.stu.score = 94;
	cout<<"老师姓名:"<<t1.name<<endl
		<<"老师id编号:"<<t1.id<<endl
		<<"老师年龄:"<<t1.age<<endl
		<<"老师教导学生的姓名:"<<t1.stu.name<<endl
		<<"老师教导学生的年龄:"<<t1.stu.age<<endl
		<<"老师教导学生的成绩:"<<t1.stu.score<<endl<<endl;
	
	cout<<"老师姓名:"<<t2.name<<endl
		<<"老师id编号:"<<t2.id<<endl
		<<"老师年龄:"<<t2.age<<endl
		<<"老师教导学生的姓名:"<<t2.stu.name<<endl
		<<"老师教导学生的年龄:"<<t2.stu.age<<endl
		<<"老师教导学生的成绩:"<<t2.stu.score<<endl;
	
	cin.get();
	return 0;
} 
