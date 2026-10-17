#include<stdio.h>
int main(){
	int x;
	for(x=2;x<100;x++){
	//镶嵌循环中的变量不能一样！！！
	    int i; 
	    	for(i=2;i<x;i++){
	    	if(x%i==0){
		    break;
		    }
	    }
	    if(i==x){printf("%d ",x);
		}
    }
    printf("\n"); 
	return 0;
} 
