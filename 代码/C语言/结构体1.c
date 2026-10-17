#include <stdio.h>

struct student
{	//定义结构体 
    char name[20];
    int age;
    char sex[10];
    char tele[13];
};//以上均为（成员变量） 

void print(struct student *p){
	printf("%s %d %s %s\n",(*p).name,(*p).age,(*p).sex,(*p).tele);
		//一定要有()括号 
	printf("%s %d %s %s\n",p->name,p->age,p->sex,p->tele);
	//->箭头操作符;'结构体指针变量'+'->'+'成员名' 
}
int main()
{
    struct student a = {"zhangsan", 20, "nan", "13846468446"};
    printf("%s %d %s %s\n", a.name, a.age, a.sex, a.tele);
    //“.”操作符;'结构体成员'+'.'+ '成员名'
    print(&a);
    return 0;
}
