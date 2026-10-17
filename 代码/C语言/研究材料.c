#include<stdio.h>
int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    int i,j,k;
    int a[m],b[m];
    for(i=0;i<m;i++){
            scanf("%d",a[i]);
    }
    for(i=0;i<m;i++){
            scanf("%d",b[i]);
    }
    int max=0;
    for(i=0;i<m;i++){
        if(a[i]>n){
            continue;
        }
        if(b[i]>=max){
            max=b[i];
        }
    }
    printf("%d",max);
}
