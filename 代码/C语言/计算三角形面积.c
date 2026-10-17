//一个三角形的三边长分别是 a、b、c，那么它的面积为  根号p(p-a)(p-b)(p-c)
//其中 p=(a+b+c)/2输入这三个数字，计算三角形的面积，四舍五入精确到 1 位小数。
//输入格式,第一行输入三个实数 a,b,c，以空格隔开。
//输出格式,输出一个实数，表示三角形面积。精确到小数点后 1 位。

#include<stdio.h>
#include<math.h>
//凡是涉及数学计算中特殊的符号一定要有math.h ！！！ 
int main(){
    double a,b,c;
    scanf("%lf %lf %lf",&a,&b,&c);
    double p,s;
    p=(a+b+c)/2;
    s= sqrt(p*(p-a)*(p-b)*(p-c));
    //sqrt意为根号！！！ 
    printf("%.1f",s);
    return 0;
}
