#include<stdio.h>

int main()
{
	//初始化
	double price=0;
	double bill=0;
	
	//读取(scanf要用lf表示小数)
	printf("请输入价钱：");
	scanf("%lf",&price);
	
	printf("请输入票面：");
	scanf("%lf",&bill);
	
	//找零
	if(bill>=price)
	{
		printf("找您%.2f元\n",bill-price);
     }
	 else{
	 	printf("金额不够，还需要支付%.2f元",price-bill);
     }
	 return 0;
 } 
