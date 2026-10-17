#include<stdio.h>
#include<string.h>
		//string.h-->为了方便字符串函数的应用 

int main(void){
	
	//原型int strlen( const char *str ) 
	char a[12]="hello world";
	
	puts(a);//输出字符串a 
	
	printf("sizeof(a)=%d\n",sizeof(a));
		//sizeof-->用来算//整个字符串数组//的长度;包括'\0'!!!
	
	printf("strlen(a)=%d\n",strlen(a));
		//strlen()用来计算字符串中//连续的字符//长度;直到遇到'\0'!!!
			 
	//原型int strcpy( char *a , char *b )或int str'n'cpy 
	 	//strcpy()遇到'\0'会结束并包含'\0'!!!
	char b1[5]="love"; 
	char b2[5]="love";
	puts(b1);//输出字符串b
	
	strcpy(b1,a);
	//直接将a'全部'复制到b里面 
	puts(b1);
	
	strncpy(b2,a,8);
	//后面一定要有'数字',确保b保存a中'字符的数量'
	//即指定b保存a中几个字符 
	puts(b2);
	
	//原型int strcmp( char *str1, char *str2 )或int str'n'cmp 
		//字符串比较是对每一个字符进行比较
		//比较的是ASICC码表中每个字符对应的'数字'
	char str1[5]="maye";
	char str2[5]="Maye";
	
	printf("str1与str2的ASICC码表一个字符数字差为%d\n",
	strcmp(str1,str2));
	//str1与str2的长度应一样,否则输出为0;两字符一样输出也为0 
	//当两个字符串中有多个不一样的字符时,只比较第一个不同字符的大小,后面的一律不比较!!!
	//前面大输出1，前面小输出-1;
	
	printf("str1与str2的ASICC码表几个字符差为%d\n",
	strncmp(str1,str2,3));
	//当两个字符串前n个中有多个不一样的字符时
	//只比较第一个不同字符的大小,后面的一律不比较!!!
	
	//原型char *strcat( char *dest, const char *src )或char *strncat
	//将src字符串拷贝到dest的尾部
	//dest要有足够的空间来容纳要拷贝的字符串 
	char x1[20]="damin";
	char x2[20]="damin";
	char y[10]="good";
	
	strcat(x1,y);
	//将y填入x1的空缺中 
	puts(x1);
	
	strncat(x2,y,3);
	//将y中3个字符填入x2的空缺中 
	puts(x2);
	
	//注以上字符串函数'一定'要在string.h的头文件条件下才能使用!!!
	return 0; 
}
