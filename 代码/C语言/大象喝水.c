//一只大象口渴了,要喝20升水才能解渴
//但现在只有一个深h厘米,底面半径为r厘米的小圆桶(h和r都是整数)
//问大象至少要喝多少桶水才会解渴。π=3.14

#include<stdio.h>
#include<math.h>
int main(){
    int h,r;
    double z;
    scanf("%d %d",&h,&r);
    z=3.14*h*r*r;
    printf("%d",(int)ceil(20000/z));
    //ceil意为向上取整 
    //在printf里面一定要给ceil定义 
    return 0;
}
