#include<stdio.h>
int main(){
	int x,s=0,S=0,a[11],b=300,i;
	for(i=0;i<12;i++){
		scanf("%d",&a[i]);
	}
	for(x=0;x<12;x++){
		s+=b;
		if(s<a[x]){printf("-%d",x+1);
		return 0;
		} s-=a[x];
	    if(s>=100){int c=(s/100)*100;
	    S+=c;
	    s-=c;
		}
	}
		printf("%d",s+1.2*S);
	return 0;
} 
