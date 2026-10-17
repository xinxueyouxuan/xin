#include <iostream>
using namespace std;

void bubble(int arr[],int len){
	int i,j;
	for(i=0;i<10;i++){ 
		for(j=0;j<9-i;j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main(){
	int i,arr[] = {98,45,546,545,21,896,51,54,86,9};
	int len = sizeof(arr)/sizeof(arr[0]);
	
	bubble(arr,len);
	
	for(i=0;i<len;i++){
		cout<<"arr["<<i<<"]="<<*(arr+i)<<endl;
	}
	
	cin.get();
	return 0;
} 
