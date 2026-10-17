#include <iostream>
using namespace std;

/*
	程序流程结构 
	1.顺序结构 
	2.选择结构 
	3.循环结构 
*/ 

int main(){
	//单行if
	cout << "请输入你的分数：" << endl;
	int  score = 0;
	cin >> score;
	if(score>=600)
		cout << "恭喜您考上985,211" << endl;
	cout << endl; 
	
	//多行if 
	if(score>=500&&score<600)
		cout << "恭喜您考上一本" << endl;
	else cout << "很遗憾你没有考上一本" << endl;
	cout << endl;
	
	//多条件if
	if(score>600)
		cout<<"恭喜您考上985,211"<<endl;
	else if(score>500)
		cout<<"恭喜您考上一本"<<endl;
	else if(score>420)
		cout<<"恭喜您考上二本"<<endl;
	else cout<<"很遗憾你没有考上本科"<<endl; 
	cout << endl; 
	
	//嵌套if
	if(score>=500){
		if(score>=600)
			cout << "恭喜您考上985,211" << endl;
		else cout << "恭喜您考上一本" << endl;
	}
	else cout << "很遗憾你没有考上一本" << endl;
	cout << endl; 
	
	//例题：找出三个数中的最大值
	int a,b,c;
	cout << "请输入a,b,c的值" << endl;
	cin >> a >> b >> c;
	if(a>b){
		if(a>c)
			cout << "最大值为a=" << a << endl;
		else cout << "最大值为c=" << c << endl;
	} 
	else{
		if(b>c)
			cout << "最大值为b=" << b << endl;
		else cout << "最大值为c=" << c << endl;
	}
	cout << endl;
	
	//三目运算符
	int max;
	max = a > b ? a : b ;
	max = max > c ? max : c ;
	cout << "max=" << max <<endl;
	
	cin.get();
	return 0;
} 
