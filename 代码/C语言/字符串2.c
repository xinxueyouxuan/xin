#include<stdio.h> 
int main(int argc, char const *argv[] )
		//argc是告诉我们argv[]有多少个字符串 
		//argv[0]是命令本身;
			//当使用Unix的符号链接时,反映符号链接的名字！！！ 
{
	int i;
	for( i=0; i<argc; i++ ){
		printf("i=%d:%s\n", i , argv[i] );
	}
	
	return 0;
}
