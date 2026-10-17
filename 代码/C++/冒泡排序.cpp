#include <iostream>
using namespace std;

int main(){
	int i,j,arr[10];
	
	for(i=0;i<10;i++)
	 	cin>>arr[i];
	
	for(i=0;i<10;i++){
		for(j=0;j<9-i;j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	cout<<"冒泡排序后"<<endl;
	for(i=0;i<10;i++)
		cout<<"arr["<<i<<"]="<<arr[i]<<endl;
	cin.get();
	return 0;
} 
