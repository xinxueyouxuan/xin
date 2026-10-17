#include<stdio.h>
int main(){
	int a,b,c,x,y,z;
	scanf("%d %d %d",&a,&b,&c);
	
	if(a<=b){
		if(a<=c){if(b>c){x=a;y=c;z=b;}
		        else{x=a;y=b;z=c;}}
		else{x=c;y=a;z=b;}}
	else{if(a>=c){if(b>c){x=c;y=b;z=a;}
	            else{x=b;y=c;z=a;}}
	    else{x=b;y=a;z=c;}}
	
	printf("%d %d %d",x,y,z);
	return  0;
} 
