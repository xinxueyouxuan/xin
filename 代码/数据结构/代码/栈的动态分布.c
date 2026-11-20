#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;

typedef struct{
	Type *data;
	int top;
}Stack;

//栈的动态初始化 
Stack *initStack(){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->data = (Type*)malloc(sizeof(Type) * MAX);
	s->top = -1;
	return s;
}

//进栈---压栈---入栈 
int push(Stack *s,Type e){
	//判断栈是否充满 
	if(s->top >= MAX-1){
		printf("栈满了\n");
		return 0;
	}
	s->top++; 
	s->data[s->top] = e;
	return 1; 
}

//出栈
Type deletepop(Stack *s,Type *e){
	if(s->top == -1){
		printf("栈是空的\n");
		return 0;
	}
	*e = s->data[s->top];
	s->top--;
	return 1;
}

//获取栈顶元素
int getTop(Stack *s,Type *e){
	if(s->top == -1){
		printf("栈是空的\n");
		return 0;
	}
	*e = s->data[s->top];
	return 1;
}

int main(){
	Stack *s = initStack();
	push(s,10);
	push(s,20);
	push(s,30);
	push(s,40);
	push(s,50);
	push(s,60);
	
	Type e;
	deletepop(s,&e);
	printf("deletepop->e=%d\n",e);
	
	getTop(s,&e);
	printf("getTop->e=%d\n",e);
	
	return 0;
}
