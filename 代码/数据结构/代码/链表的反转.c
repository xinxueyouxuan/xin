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

//反转链表
Node *reverseList(Node* head){
	Node *first = NULL;
	Node *second = head->next;
	Node *third;
	
	while(second != NULL){
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	
	Node *hd = initList();
	hd->next = first;
	
	return hd;
} 

//删除中间节点
int delMiddleNode(Node *head){
	Node *fast = head->next;
	Node *slow = head;
	
	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}
	Node *q = slow->next;
	slow->next = q->next;
	free(q);
	return 1;
} 

//链表重新排序
void reList(Node *head){
	Node *fast = head->next;
	Node *slow = head;
	
	while(fast != NULL && fast->next != NULL){
		fast = fast->next->next;
		slow = slow->next;
	}
	
	Node *first = NULL;
	Node *second = slow->next;
	slow->next = NULL;
	Node *third = NULL;
	
	//反转链表 
	while(second != NULL){
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	
	Node *p1 = head->next;
	Node *q1 = first;
	Node *p2,*q2;
	while(p1 != NULL && q1 != NULL){
		p2 = p1->next;
		q2 = q1->next;
		
		p1->next = q1;
		q1->next = p2;
		
		p1 = p2;
		q1 = q2;
	}
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
	
	Node *tail = get_tail(list);
	
	tail = insertTail(tail,1);
	tail = insertTail(tail,2);
	tail = insertTail(tail,3);
	tail = insertTail(tail,4);
	tail = insertTail(tail,5);
	tail = insertTail(tail,6);
	tail = insertTail(tail,7);
	listNode(list);
	
	Node* reverse = reverseList(list);
	listNode(reverse);
	
	delMiddleNode(reverse);
	listNode(reverse);
	
	reList(reverse);
	listNode(reverse);
	
	return 0;
}
