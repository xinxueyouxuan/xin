#include<stdio.h>
#include<ctype.h>//大小写转换 
int main(void){
	int c;
	printf("复制输入到输出\n输入文本(Ctrl+z结束)：\n");
	while((c=getchar())!=EOF){
		putchar(c);
	} 
	//复制输入到输出 
	
	int count = 0;
	printf("统计字符数\n输入文本：\n");
	while(getchar()!='\n'){//'\n'-->换行 
		count++;
	}
	printf("字符数:%d\n",count);
	//统计字符数 
	
	int a;
	printf("回显并转换大小写\n请输入文本(Ctrl+z结束):\n");
	while((a=getchar())!=EOF){
		if(islower(a))
			putchar(toupper(a));
		else if(isupper(a))
			putchar(tolower(a));
		else
			putchar(a);
	}
	//回显并转换大小写 
	
	//			putchar()				getchar() 
	//功能		输出字符				输入字符 
	//参数		int(字符) 				无 
	//返回值	*输出*的字符或EOF 		*读取*的字符或EOF 
	//效率		高(单字符*输入*) 		高(单字符输入) 
	//缓冲区	 无缓冲区问题 			有缓冲区问题 
	
	return 0;
} 
