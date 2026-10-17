#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct node{
	Type data;
	struct node *next;
}Node;

//初始化链表
Node *initList(){
	//申请一块区域存放链表头节点 
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
} 

//尾插法遍历
//找到尾部 
Node *get_tail(Node *L){
	Node *p = L;
	while(p->next != NULL){
		p = p->next;
	}
	return p;
}

//尾插法
Node *insertTail(Node *L,Type e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	L->next = p;
	p->next = NULL;
	return p;
} 

//判断链表是否有环
int isCycle(Node *head){
	Node *fast = head;
	Node *slow = head;
	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow)
			return 1;
	}
	return 0;
}

void listNode(Node *L){
	Node *p = L->next;
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
} 

int main(){
	Node *list = initList();
	
	Node *tail =  get_tail(list);
	
	tail = insertTail(tail,1);
	tail = insertTail(tail,2);
	tail = insertTail(tail,3);
	Node *t = tail;
	tail = insertTail(tail,4);
	tail = insertTail(tail,5);
	tail = insertTail(tail,6);
	tail = insertTail(tail,7);
	tail = insertTail(tail,8);
	tail = insertTail(tail,9);
	tail->next = t;
	
	if(isCycle(list)){
		printf("有环\n");
	}
	else{
		printf("无环\n");
	}
	
	return 0;
}
