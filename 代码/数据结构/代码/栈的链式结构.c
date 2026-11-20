#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;

typedef struct stack{
	Type data;
	struct stack *next;
}Stack;

Stack *initStack(){
	Stack *s = (Stack*)malloc(sizeof(Stack));
	s->data = 0;
	s->next = NULL;
	return s;
}

//判断栈是否为空 
int isEmpty(Stack *s){
	if(s->next == NULL){
		printf("栈是空的\n");
		return 1;
	}
	else{
		return 0;
	} 
}

//进栈---压栈 
int push(Stack *s,Type e){
	Stack *p = (Stack*)malloc(sizeof(Stack));
	p->data = e;
	p->next = s->next;
	s->next = p;
	return 1;
}

//出栈
int deletepop(Stack *s,Type *e){
	if(s->next == NULL){
		printf("栈是空的\n");
		return 0;
	}
	*e = s->next->data;
	Stack *q = s->next;
	s->next = q->next;
	free(q);
	return 1;
} 

//获取栈顶元素
int getTop(Stack *s,Type *e){
	if(s->next == NULL){
		printf("栈是空的\n");
		return 0;
	}
	*e = s->next->data;
	return 1;
}

int main(){
	Stack *s = initStack();
	push(s,10);
	push(s,20);
	push(s,30);
	push(s,40);
	
	Type e;
	
	getTop(s,&e);
	printf("getTop->e=%d\n",e);
	
	deletepop(s,&e);
	printf("deletepop->e=%d\n",e);
	
	getTop(s,&e);
	printf("getTop->e=%d\n",e);
	
	return 0;
}
