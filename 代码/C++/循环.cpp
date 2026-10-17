#include <iostream>
using namespace std;

int main(){
	int i=0,n,s=0;
	cout<<"请输入n的值,计算前n项自然数的和"<<endl;
	cout<<"n=";
	cin>>n;
	//while循环 
	while(i<=n){
		s+=i;
		i++;
	}
	cout<<"前"<<n<<"项自然数的和为"<<s<<endl; 
	cout<<endl;
	//do{}while循环 
	i=0,s=0;
	do{
		s+=i;
		i++; 
	}while(i<=n);
	cout<<"前"<<n<<"项自然数的和为"<<s<<endl;
	cout<<endl;
	//for循环 
	s=0;
	for(i=0;i<=n;i++){
		s+=i;
	}
	cout<<"前"<<n<<"项自然数的和为"<<s<<endl;
}
