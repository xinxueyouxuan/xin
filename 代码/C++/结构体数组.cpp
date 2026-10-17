#include <iostream>
#include <cstring>
using namespace std;

struct student{
	string name;
	int age;
	int score;
};

int main(){
	//创建结构体数组 
	struct student arr[3]={
		{"张三",18,80},
		{"李四",19,97},
		{"王五",20,89},
	};
    arr[2].name = "赵六";
	arr[2].age = 22;
	arr[2].score = 99;
	int i;
	for(i=0;i<3;i++){
		cout<<"姓名:"<<arr[i].name<<endl
			<<"年龄:"<<arr[i].age<<endl
			<<"分数:"<<arr[i].score<<endl<<endl;
	} 
	
	cin.get();
    return 0;
}
