#include<stdio.h>
//NULL表示零地址
//不同类型的指针不能相互赋值 
int main(void){
	char ac[]={0,1,2,3,4,5,6,7,8,9,};
	//根据数组类型，char储存数据需要一个字节的内存单元
	//sizeof（char）=1
	char *p1=ac;
	char *pp1=&ac[5];
//	*p    <-->  ac[0]
//	*(p+1)<-->  ac[1] 
//	*(p+n)<-->  ac[n]
	printf("*p1+1=%p\n",p1+1);
	printf("*(p1+1)=%d\n",*(p1+1));
	printf("pp1-p1=%d\n",pp1-p1);
	
	int i;
	for(i=0;i<sizeof(ac)/sizeof(ac[0]);i++){
		printf("ac[%d]=%d\n",i,*(p1+i));}//*(p1+i)等价于i 
 
//	for(p1=ac ;*p1 !=-1;p1++ ){
	while( *p1 != -1 ){
		printf("*p1=%d\n",*p1++);//有点问题 
	}
	
	
	int ai[]={0,1,2,3,4,5,6,7,8,9,};
	//而sizeof（int）=4 
	int *p2=ai;
	int *pp2=&ai[6];
	printf("*p2=%p\n",p2);
	printf("*p2+1=%p\n",p2+1);
	printf("*(p2+1)=%d\n",*p2+1);
	printf("pp2=%p\n",pp2);
	printf("pp2-p2=%d\n",pp2-p2);
//	指针相减的结果是这两个地址的差除以sizeof（他们的类型）！！！
//	即这两个地址之间有几个这样类型的东西///能放几个这样类型的东西 
	printf("p1=%d\np2=%d\n",p1,p2);
	p1=p2;//虽然程序仍可以运行但会有警告！！！ 
	printf("p1=%d\n",p1) ;
	return 0;
} 
