#include <iostream>
#include <cstring> 

#define MAX 1000 

using namespace std;

//定义个人结构体 
struct person{
	string name;
	string sex;
	int age;
	string phone;
	string address;
};

//定义总体通讯录 
struct addressbooks{
	struct person personarr[MAX];
	//记录联系人个数 
	int size;
};

//生成菜单 
void showmenu(){
	
	cout<<"**********************"<<endl
		<<"*****1.添加联系人*****"<<endl
		<<"*****2.显示联系人*****"<<endl
		<<"*****3.删除联系人*****"<<endl
		<<"*****4.查找联系人*****"<<endl
		<<"*****5.修改联系人*****"<<endl
		<<"*****6.清空联系人*****"<<endl
		<<"*****0.退出通讯录*****"<<endl
		<<"**********************"<<endl;
		
} 

//添加联系人 
void addperson(addressbooks *abs){
	
	if(abs->size==MAX){
		cout<<"通讯录已满，无法添加"<<endl;
	}
	
	else{
		
		//定义一个字符串数组用于存储名字 
		string name;
		cout<<"请输入姓名："<<endl;
		cin>>name;
		abs->personarr[abs->size].name = name;
		
		cout<<"请输入性别"<<endl;
		cout<<"1 男"<<endl;
		cout<<"2 女"<<endl;
		//定义一个字符串用来存储性别 
		string sex;
		cin>>sex;
		abs->personarr[abs->size].sex = sex;
		
		cout<<"请输入年龄"<<endl;
		//定义一个变量用来存储年龄 
		int age = 0;
		cin>>age;
		abs->personarr[abs->size].age = age;
		
		cout<<"请输入联系人电话"<<endl;
		string phone;
		cin>>phone;
		abs->personarr[abs->size].phone = phone;
		
		cout<<"请输入家庭住址"<<endl;
		string address;
		cin>>address; 
		abs->personarr[abs->size].address = address;
		
		//更新通讯录人数 
		abs->size++; 
		cout<<"添加成功"<<endl; 
	}
	
	system("pause");
	system("cls");//清屏 
}

//显示联系人 
void showperson(addressbooks *abs){
	if(abs->size == 0){
		cout<<"当前记录为空"<<endl;
	}
	
	else {
		
		int i=0;
		
		for(i=0;i<abs->size;i++){
			cout<<"姓名:"<<abs->personarr[i].name<<endl;
			cout<<"性别:"<<abs->personarr[i].sex<<endl;
			cout<<"年龄:"<<abs->personarr[i].age<<endl;
			cout<<"电话:"<<abs->personarr[i].phone<<endl;
			cout<<"住址:"<<abs->personarr[i].address<<endl;
		}
	}
	
	system("pause");
	system("cls"); 
}

//联系人是否存在,存在返回具体位置，不存在返回-1 
int isexist(addressbooks *abs,string name){
	
	int i;
	
	for(i=0;i<abs->size;i++){
		if(abs->personarr[i].name==name){
			return i;
		}
	}
	
	return -1;//没找到返回-1 
} 

//删除指定联系人
void deleteperson(addressbooks *abs){
	
	cout<<"请输入要删除的联系人"<<endl;
	
	string name;
	cin>>name;
	
	int ret = isexist(abs,name);
	
	if(ret != -1){
		
		int i =  ret;
		
		for(i=ret ; i < abs->size ;i++){
			abs->personarr[i] = abs->personarr[i+1];
			}
			
		abs->size--;
		cout<<"删除成功"<<endl;
	}
	
	else{
		cout<<"查无此人"<<endl;
	}
} 

//查找联系人
void findperson(addressbooks *abs){
	
	cout<<"请输入您要查找的联系人"<<endl;
	
	string name;
	cin>>name;
	
	int ret = isexist(abs,name);
	
	if(ret != -1 ){
		cout<<"姓名："<<abs->personarr[ret].name<<endl;
		cout<<"性别："<<abs->personarr[ret].sex<<endl;
		cout<<"年龄："<<abs->personarr[ret].age<<endl;
		cout<<"电话："<<abs->personarr[ret].phone<<endl;
		cout<<"住址："<<abs->personarr[ret].address<<endl;
	}
	
	else{
		cout<<"查无此人"<<endl;
	}
	
	system("pause");
	system("cls");
} 

//修改联系人
void modifyperson(addressbooks *abs){
	cout<<"输入你要修改的联系人"<<endl;
	
	string name;
	cin>>name;
	
	int ret = isexist(abs,name);
	
	if(ret != -1){
		string name;
		cout<<"请输入修改后的姓名"<<endl;
		
		cin>>name;
		abs->personarr[ret].name = name;
				
		string sex;
		cout<<"请输入修改后的性别"<<endl;
		cout<<"1.男"<<endl;
		cout<<"2.女"<<endl;
		
		cin>>sex;
		abs->personarr[ret].sex = sex;
		
		int age;
		cout<<"请输入修改后的年龄"<<endl;
		
		cin>>age;
		abs->personarr[ret].age = age;
		
		string phone;
		cout<<"请输入修改后的电话"<<endl;
		
		cin>>phone;
		abs->personarr[ret].phone = phone;
		
		string address;
		cout<<"请输入修改后的住址"<<endl;
		
		cin>>address;
		abs->personarr[ret].address = address;
		
		cout<<"修改成功!"<<endl; 
	}
	
	else{
		cout<<"查无此人"<<endl;
	}
	
	system("pause");
	system("cls");
} 

//清空联系人
void cleanperson(addressbooks *abs){
	
	abs->size = 0;
	
	cout<<"通讯录已清空"<<endl;
	
//	system("pause");
//	system("cls");
} 

int main(){
	
	addressbooks abs;
	
	abs.size = 0;
	 
	int select = 0;
	
	while(true){
		
		showmenu();
		cin >> select;
		
		switch(select){
			
			case 0:
				cout<<"欢迎下次使用"<<endl;
				cin.get(); 
				return 0; 
				break; 
				
			case 1:
				addperson(&abs);
				break;
				
			case 2:
				showperson(&abs); 
				break;
				
			case 3:
//				{ 
//					cout<<"请输入联系人姓名："<<endl;
//					string name;
//					cin>>name;
//					int ret = isexist(&abs,name);
//					if(ret == -1){
//						cout<<"查无此人"<<endl;
//					}
//					else{
//						int i =  ret;
//						for(i=ret ; i < abs->size ;i++){
//							abs->personarr[i] = abs->personarr[i+1];
//						}
//						abs->size--;
//						cout<<"删除成功"<<endl;
//					}
//					system("pause");
//					system("cls");
//				}
				deleteperson(&abs);
				system("pause");
				system("cls");
				break;
				
			case 4:
				findperson(&abs); 
				break;
				
			case 5:
				modifyperson(&abs);
				break;
				
			case 6:
				cout<<"你是否确定要清空通讯录"<<endl;
				cout<<" 1   -->确定"<<endl;
				cout<<"其他 -->取消"<<endl;
				int x;
				cin>>x;
				
				if(x == 1){
					cleanperson(&abs);
				}
				
				else{
					cout<<"已取消清空通讯录"<<endl;
				} 
				system("pause");
				system("cls"); 
				break;
				
			default:
				break;
				
		}
	}
	
	system("pause");
	return 0;
	
} 
