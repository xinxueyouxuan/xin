#include<stdio.h>
int main (){
	int x,i;
	int count[10] = {0};
	scanf("%d",&x);
	
	while(x!=-1){
		if(x>=0&&x<=9){
			count[x]++;
		}
		scanf("%d",&x);
	}
	
	for ( i=0; i <= 9; i++){
	printf("%d:%d\n",i,count[i]);
	}
	
	return 0;
}
