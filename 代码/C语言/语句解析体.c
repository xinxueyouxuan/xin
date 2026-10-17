//题目：一串长度不超过 255 的 PASCAL 语言代码，只有 a,b,c 三个变量，而且只有赋值语句，
	//赋值只能是一个一位的数字或一个变量，每条赋值语句的格式是 [变量]:=[变量或一位整数];
	//未赋值的变量值为 0 输出 a,b,c 的值

//输入：一串符合语法的 PASCAL 语言，只有 a,b,c 三个变量，而且只有赋值语句，
	//赋值只能是一个一位的数字或一个变量，未赋值的变量值为 0。

//例：输入a:=3;b:=4;c:=5;
//输出 3 4 5
#include<stdio.h>
int main(void){
    int i,a=0,b=0,c=0;//直接令abc为0，方便后续程序运行 
    char s[256];//题目要求不超过255，但'\0'也要占一位 
    scanf("%s",s);
    for(i=0;s[i]!='\0';i++){//s[i]!='\0'，此条件大幅度减少了循环次数 
        if(s[i]=='a'||s[i]=='b'||s[i]=='c'){
            char x=s[i];// 保存变量名
            if(s[i+1]==':' && s[i+2]=='='){
                i += 3;// 跳过变量名':''='，现在指向赋值内容
                if(s[i]>='0'&&s[i]<='9'){
                    int number=s[i]-'0';//字符转数字 
                    if(x=='a')a=number;
                    else if(x=='b')b=number;
                    else if(x=='c')c=number;
                }
                else if(s[i]=='a'||s[i]=='b'||s[i]=='c'){
                    int m;//定义m用于储存 
                    if(s[i]=='a')m=a;
                    else if(s[i]=='b')m=b;
                    else if(s[i]=='c')m=c;

                    if(x=='a')a=m;
                    else if(x=='b')b=m;
                    else if(x=='c')c=m;
                }
            }
        }
    }
    printf("%d %d %d\n",a,b,c); 
    return 0;
}
