#include<stdio.h>
long a(int n){
    return (n<=1)? 1 : n*a(n-1);
}
int main(void){
    int n;
    scanf("%d",&n);
    printf("%ld",a(n));
    return 0;
}
