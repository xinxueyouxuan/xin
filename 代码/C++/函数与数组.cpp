#include <iostream>
using namespace std;

int main(){
	int i,a[10]={1,2,3,4,5,6,7,8,9,10};
	int *p = a;
	cout<<"*p="<<*p<<endl;
	cout<<"*(++p)="<<*(++p)<<endl;
	cout<<endl;
	
	cout<<"p="<<p<<endl;
	cout<<"++p="<<++p<<endl;
	cout<<endl;
	
	int *p1=a;
	for(i=0;i<10;i++,*p1++){
		cout<<"*p1="<<*p1<<endl;
	}
	
	cin.get();
	return 0;
}
