#include<stdio.h>
#include<string.h>
int main(){
    int k;
    char s[100];
    scanf("%d",&k);
    scanf("%s",&s); 
    int i,j,x=1;
    for(i=0;i<100;i++){
        if(s[i]==0)
            break;
        x++;
    }
    for(i=x-k-1;i<x;i++){
       printf("%c",s[i]);
    }
    for(i=0;i<x-k-1;i++){
        printf("%c",s[i]);
    }
    return 0;
}
