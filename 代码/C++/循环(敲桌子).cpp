#include <iostream>
using namespace std;

int main(){
	int i,x,y,z,n;
	cout<<"请输入1000以内的最终值n=";
	cin>>n;
	if(n<1000) 
	for(i=1;i<=n;i++){
		if(i<100){
			x=i%10,y=i/10;
			if(x==7||y==7||i%7==0)
				cout<<i<<"敲桌子"<<endl;
			else cout<<i<<endl;
		}
		else {
			x=i%10,y=(i/10)%10,z=i/100;
			if(x==7||y==7||z==7||i%7==0)
				cout<<i<<"敲桌子"<<endl;
			else cout<<i<<endl;
		}
	}
	else cout<<"输入的n太大了"<<endl;
	cin.get();
	return 0;
}
