#include <iostream>
using namespace std;

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
	int a = 10,b = 20;
	int *pa = &a,*pb = &b;
	swap(pa,pb);
	cout<<"a="<<a<<endl;
	cout<<"*pa="<<*pa<<endl;
	cout<<"b="<<b<<endl;
	cout<<"*pb="<<*pb<<endl;
	
	cin.get();
	return 0;
} 
