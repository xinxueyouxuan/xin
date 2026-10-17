#include <iostream>
#include <cstring>
using namespace std;

struct student{
	string name;
	int age;
	int score;
};

int main(){
	student t,s[4]={
		{"张三",18,80},
		{"李四",19,97},
		{"王五",20,89},
		{"赵六",22,99},
	};
	//结构体't'是用来作为第三方
	//交换两个结构体的值的中间变量 
	
	student *p = &s[0];
	cout<<"姓名:"<<p->name<<"  "
		<<"年龄:"<<p->age<<"  "
		<<"分数:"<<p->score<<endl<<endl;
	
	cout<<"按成绩从大到小排名："<<endl; 
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3-i;j++){
			if(s[j].score<s[j+1].score){
				t=s[j],s[j]=s[j+1],s[j+1]=t;
			}
		}
	}
	for(i=0;i<4;i++){
		cout<<"姓名:"<<s[i].name<<endl
			<<"年龄:"<<s[i].age<<endl
			<<"分数:"<<s[i].score<<endl<<endl;
	} 
	
	cin.get();
	return 0;
} 
