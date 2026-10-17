#include <iostream>
using namespace std;

int main(){
	int i,x,y;
	cout<<"500以内如果遇到";
	cin>>x;
	cout<<x<<"的倍数则跳过"<<endl; 
	cout<<"如果遇到";
	cin>>y;
	cout<<"则退出"<<endl;
	for(i=0;i<=500;i++){
		if(i==y)break;
		if(i%x==0){
			cout<<i<<"是x="<<x<<"的倍数"<<endl;
			continue;
		}
		else cout<<i<<endl;
	}
	cin.get();
	return 0;
}
