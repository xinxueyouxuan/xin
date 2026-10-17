#include <iostream>
using namespace std;

int main(){
	int i,j,n;
	cout<<"请输入矩阵的大小n=";
	cin>>n;
	char x;
	cout<<"请输入矩阵的字符x=";
	cin>>x;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			cout<<x;
			if(j<n-1)
				cout<<" ";
		}
		cout<<endl;
	}
	cin.get();
	return 0;
}
