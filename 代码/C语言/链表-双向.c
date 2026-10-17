#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct node{
	Type data;
	struct node *next,*prev;
}Node;

//双向链表的初始化 
Node *initList(){
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->prev = NULL;
	head->next = NULL;
	return head;
}

//双向链表的头插法
Type insertHead(Node *L,Type e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->prev = L;
	p->next = L->next;
	if(L->next != NULL){
		L->next->prev = p;
	}
	L->next = p;
	return 1;
}

//双向链表的尾插法 
//尾插法遍历,找到尾部 
Node *get_tail(Node *L){
	Node *p = L;
	while(p->next != NULL){
		p = p->next;
	}
	return p;
}
Node *insertTail(Node *L,Type e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->prev = L;
	L->next = p;
	p->next = NULL;
	return p;
} 

//双向链表指定位置插入
int  insertNode(Node *L,int pos,Type e){
	Node *p = L;
	int i=0;
	while(i<pos-1){
		p = p->next;
		i++;
		if(p == NULL)
			return 0;
	}
	
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->prev = p;
	q->next = p->next;
	p->next->prev = q;
	p->next = q;
	return 1; 
}

//双向链表的删除节点
int deleteNode(Node *L,int pos){
	Node *p = L;
	int i=0;
	while(i<pos-1){
		p = p->next;
		i++;
		if(p == NULL)
			return 0;
	}
	
	if(p->next == NULL){
		printf("要删除的位置错误\n");
	}
	
		Node *q = p->next;
		p->next = q->next;
		if(q->next != NULL)
			q->next->prev = p;
		free(q);
	return 1;
} 

void listNode(Node *L){
	Node *p = L->next;
	if(p == NULL){
		printf("链表仅有头节点\n");
	}
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
} 

//清空链表
void  freeNode(Node *L){
	Node *p = L->next;
	Node *q;
	while(p != NULL){
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
}

int main(){
	Node *list1 = initList();
	Node *list = initList();
	
	insertHead(list1,10);
	insertHead(list1,20);
	insertHead(list1,30);
	insertHead(list1,40);
	insertHead(list1,50);
	listNode(list1);
	
	Node *tail=get_tail(list);
	tail = insertTail(tail,10);
	tail = insertTail(tail,20);
	tail = insertTail(tail,30);
	tail = insertTail(tail,40);
	tail = insertTail(tail,50);
	tail = insertTail(tail,60);
	listNode(list);
	
	insertNode(list,2,15);
	listNode(list);
	
	deleteNode(list,7);
	listNode(list);
	deleteNode(list,2);
	listNode(list);
	
	freeNode(list);
	listNode(list);
	
	return 0;
}
