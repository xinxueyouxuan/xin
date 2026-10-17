//输入一个小写字母，输出其对应的大写字母。
//例如输入 q[回车] 时，会输出 Q。

#include<stdio.h>
int main(){
    char a;
    scanf("%c",&a);
    a=a-32;
    //小写字母在ASCII表中比大写字母大32 
    printf("%c",a);
    return 0;
}
