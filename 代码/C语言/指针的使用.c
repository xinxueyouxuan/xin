#include<stdio.h>
void swap(int *pa,int *pb)
//交换两个变量
{
	int t=*pa;
	*pa = *pb;
	*pb = t;
 }
void minmax(int a[],int *min,int *max)
//找最大值 
{
	int i=0;
	for(i=1;i<11;i++){
		if(a[i]>*max)*max=a[i];
        if(a[i]<*min)*min=a[i];
	}
}
int main(void){
 	int a=5,b=6;
 	swap(&a,&b);
 	printf("a=%d b=%d\n",a,b);
    int m[] = {1,2,3,4,5,6,7,8,9,12,43,};
	int max,min;
    max=m[0];min=m[0];
    minmax(m,&min,&max);
    printf("min=%d max=%d",min,max);
 	return 0;
 }
