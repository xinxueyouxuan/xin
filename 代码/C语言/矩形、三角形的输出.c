#include<stdio.h>
int main(){
	int n,i,j;
	scanf("%d",&n);
	int m=1;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%02d",m);
			m++;
		}
		printf("\n");
	}
	printf("\n"); 
	m=1;
	for(i=1;i<=n;i++){
		for(j=0;j<2*(n-i);j++){
            printf(" ");
        }
		for(j=1;j<=i;j++){
			printf("%02d",m);
			m++; 
		}
		printf("\n");
	}
	return 0;
} 
