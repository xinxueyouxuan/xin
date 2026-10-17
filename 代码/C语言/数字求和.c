#include<stdio.h>
int main(void){
    int n;
    scanf("%d",&n);
    int a=0,s=0;
    do{
        s=s+n%10;
        n/=10;
        
    }while(n>0);
    printf("%d",s);
    return 0;
}
