#include<stdio.h>
int main(){
    int n,i,a[1000];
    scanf("%d",&n);
    for(i=1;n!=1;i++){
        a[i]=n;
        if((n%2)==0){
            n/=2;
        }else{
            n = n * 3+1;
        }
    }a[i]=1; 
    for(i;i>=1;i--){
        printf("%d",a[i]);
        if(i>0)printf(" ");
    }  
    return 0;
}
