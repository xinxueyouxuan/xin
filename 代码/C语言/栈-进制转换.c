#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;

typedef struct{
	Type data[MAX];
	int top;
}Stack;

void iniStack(Stack *s){
	s->top = -1;
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

//十进制转二进制
void d2b(int decimal){
    Stack s;
    iniStack(&s);
    
    while(decimal > 0){
        push(&s, decimal % 2);
        decimal /= 2;
    }
    
    printf("二进制表示为: ");
    while(s.top != -1){
        Type e;
        deletepop(&s, &e);
        printf("%d", e);
    }
    printf("\n");
}


//十进制转八进制
void d2o(int decimal){
    Stack s;
    iniStack(&s);
    
    while(decimal > 0){
        push(&s, decimal % 8);
        decimal /= 8;
    }
    
    printf("八进制表示为: ");
    while(s.top != -1){
        Type e;
        deletepop(&s, &e);
        printf("%d", e);
    }
    printf("\n");
}

//十进制转十六进制
void d2h(int decimal){
    Stack s;
    iniStack(&s);
    
    while(decimal > 0){
        push(&s, decimal % 16);
        decimal /= 16;
    }
    
    printf("十六进制表示为: ");
    while(s.top != -1){
        Type e;
        deletepop(&s, &e);
        printf("%X", e);
    }
    printf("\n");
}

int main(){
	Stack s;
	iniStack(&s);
	
    int x;
    printf("请输入一个十进制整数: ");
    scanf("%d", &x);

	d2b(x);
	d2o(x);
	d2h(x);
	
	return 0;
}