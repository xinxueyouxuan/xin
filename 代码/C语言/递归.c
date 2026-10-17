#include <stdio.h>

//非递归 
int fun(int n){
	int sum = 0;
	int i;
	for(i = 1;i <= n;i++){
		sum += i;
	}
	return sum;
}

//递归
int func(int n){
	if(n == 1){
		return 1;
	}
	else return n + func(n-1);
}

//斐波那契数列-非递归
int Fibo(int n){
	int a1 = 1;
	int a2 = 1;
	int x = 0;
	int i;
	for(i = 3;i <= n;i++){
		x = a1 + a2;
		a1 = a2;
		a2 = x;
	}
	return x;
} 

//斐波那契数列-递归 
int Fiboc(int n){
	if(n == 1 || n == 2){
		return 1;
	}
	else
		return Fiboc(n - 1) + Fiboc(n - 2);
}

int main(){
	printf("fun(10)=%d\n",fun(10));
	printf("func(10)=%d\n\n",func(10));
	
	printf("Fibo(20)=%d\n",Fibo(20));
	printf("Fiboc(20)=%d\n",Fiboc(20));
	
	return 0;
} 
