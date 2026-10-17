#include<stdio.h>

int main(){
	char a;
	//char是用来储存字符，处理文本数据 
	scanf("%c",&a);
	//%c是输入输出字符的 
	printf("  %c\n",a);
	printf(" %c%c%c\n",a,a,a);
	printf("%c%c%c%c%c\n",a,a,a,a,a);
	
	return 0;
}
