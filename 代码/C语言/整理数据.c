#include<stdio.h>
int main(void){
    int n,k;
    scanf("%d %d",&n,&k);
    int a[n],i,j,min[n];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
        min[i]=a[0];
    }
    min[0]=a[0];
    for(i=1;i<n;i++){
        if(min[0]>a[i])
            min[0]=a[i];
    }
    for(i=1;i<n;i++){
        for(j=0;j<n;j++){
            if(a[j]>min[i-1]&&min[i]>=a[j])
                min[i]=a[j];
        }
        printf("min[%d]=%d\n",i,min[i]); 
    }
    printf("%d",min[k-1]);
    return 0;
}
