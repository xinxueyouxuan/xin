#include <iostream>
using namespace std;

int maxs(int a,int b,int c){
	int max=a;
	max = max>b? max:b;
	max = max>c? max:c;
	return max;
}

int main(){
	int a,b,c,max;
	cout<<"请输入3个数"<<endl; 
	cin>>a>>b>>c;
	
	max=maxs(a,b,c);
	
	cout<<"三个数"
		<<a<<","<<b<<","<<c<<","
		<<"中最大值max="<<max<<endl;
	
	cin.get();
	return 0;
}
