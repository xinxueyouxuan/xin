#include<stdio.h>
int main(){
    int n,i,j,k,x=0;
    scanf("%d",&n);
    int number[n];
    for(i=0;i<n;i++)
        scanf("%d",&number[i]);
    int count[100]={0};
    for(i=0;i<n;i++){
        if(count[i])continue;
        for(j=0;j<n;j++){
            if(i==j)continue;
            for(k=j+1;k<n;k++){
                if(k==i||k==j)continue;
                if(number[k]+number[j]==number[i]){
                    x++;
                    count[i]=1;
                    break;
                }
            }
            if(count[i])break;
        }
    }
    printf("%d",x);
    return 0;
}
