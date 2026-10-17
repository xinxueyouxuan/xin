#include<stdio.h>
int search(int x,int a[],int l){
	int z=-1;
	int i;
	for(i=0; i <l;i++){
		if(x=a[i])
		z=i;
		break;
	} 
	return z;//输出z 
}
int main(void){
	int a[]={2,4,6,7,1,3,5,9,111,13,23,14,32};
	int x,l;
	int size;
	l=sizeof(a)/sizeof(a[0]);//计算数组a[]有多少个数(用字符的计算)
	printf("请输入数字\n");
	scanf("%d",&x);
	size=search(x,a,l);
	if(size!=-1)
	printf("%d在%d这个位置上\n",x,size);
	else
	printf("%d不存在\n",x);
	return 0;
}
