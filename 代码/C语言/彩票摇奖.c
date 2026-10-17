#include<stdio.h>
int main(){
    int win[34]={0}; 
    int n,i,j,k,mun;
    scanf("%d",&n);
    int a[7],count[8]={0};
    for(i=0;i<7;i++){
        scanf("%d",&mun);
        win[mun]=1;
    }
    
    for(i=0;i<n;i++){
    	int x=0;
    	for(j=0;j<7;j++){
    		scanf("%d",&a[j]);
			if(win[a[j]])
			x++;
			}
		count[x]++;
	}
    for(i=7;i>0;i--){
    	printf("%d",count[i]);
    	if(i>0)printf(" ");
	}
    return 0;
}
