#include <iostream>
using namespace std;

int main(){
	int i,j,arr[2][2],s=0;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			cin>>arr[i][j];
			s+=arr[i][j];
		}
	}
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			cout<<"元素arr["<<i<<"]["<<j<<"]="<<arr[i][j]<<endl;
		}
	}
	cout<<"数组arr[2][2]所有元素和为"<<s<<endl;
	
	cin.get();
	return 0;
} 
