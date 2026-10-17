#include <iostream>
#include <string>
using namespace std;

/*
	封装二.类在设计时，可以把行为和属性放在不同的权限下，加以控制
		访问权限有三种
		1.public	公共权限	类内可以访问 类外可以访问 
		2.protected	保护权限 	类内可以访问 类外不可以访问  儿子可以访问父亲中保护的内容 
		3.private	私有权限 	类内可以访问 内外不可以访问  儿子不可以访问父亲的私有内容 
*/

class person 
{
public:
	string name;
	
protected:
	string car;
	
private:
	int password;

public:
	void func(){
		name = "张三";
		car = "拖拉机";
		password = 123456;
		
		cout<<name<<endl<<car<<endl<<password<<endl; 
	}
}; 

int main(){
	
	person p1;
	
	p1.name = "李四";
	//p1,car = "奔驰"; 
	//保护权限的内容在类外访问不到
	//p1.password = 123; 
	//私有权限的内容也访问不到
	p1.func(); 
	
	cin.get();
	return 0;
} 
