#include<stdio.h>
int main(void){
    int n,i,j,x=0;
    scanf("%d",&n);
    int a[n],b[n],c[n],s[n];
    for(i=1;i<=n;i++){
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        s[i]=a[i]+b[i]+c[i];
    }
    for(i=2;i<=n;i++){
        for(j=1;j<i;j++){
            if((a[i]-a[j])>=-5&&(a[i]-a[j])<=5&&(b[i]-b[j])>=-5&&(b[i]-b[j])<=5&&(c[i]-c[j])>=-5&&(c[i]-c[j])<=5&&(s[i]-s[j])>=-10&&(s[i]-s[j])<=10)x++;
        }
    }
    printf("%d",x);
    return 0;
}
