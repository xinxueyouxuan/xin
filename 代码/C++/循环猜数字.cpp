#include <iostream>
#include <ctime>	//提供time()函数 
#include <cstdlib>	//提供srand()和rand()函数 
using namespace std;

int main(){
	srand(time(NULL));
	//用当前时间(秒数)作为种子,初始化随机数生成器,使rand()每次生成的随机数不同 
	int times=time(NULL);
	cout<<"times=time(NULL)="<<times<<endl; 
	int x;
	//生成0~100的随机数 
	x = rand()%101;
	int a;
	cout<<"输入你所猜测的数字"<<endl; 
	cin>> a;
	for(;a!=x;){
		if(a>x)
			cout<<"你猜的数大了"<<endl;
		else cout<<"你猜的数小了"<<endl;
		cout<<"请继续输入"<<endl;
		cin>>a;
	}
	cout<<"恭喜你猜对了,随机数是"<<x<<endl;
	cin.get();
	return 0;
} 
