#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct node{
	Type data;
	struct node *next;
}Node;

Node *initlist(){
	Node *head = (Node*)malloc(sizeof(Node));
	head->data = 0;
	head->next = NULL;
	return head;
} 

//头插法
int insertHead(Node *L,Type e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
}

int findNode(Node *L,int k){
	Node *fast = L->next;
	Node *show = L->next;
	
	int i;
	for(i=0;i<k;i++){
		fast = fast->next;
		if(fast==NULL){
			printf("没有这个节点\n");
			return 0; 
		}
	}
	while(fast != NULL){
		fast = fast->next;
		show = show->next;
	}
	printf("倒数第%d个节点为%d\n",k,show->data);
} 

//遍历 
void listNode(Node *L){
	Node *p = L->next;
	while(p != NULL){
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
} 

int main(){
	Node *list = initlist();
	
	insertHead(list,10);
	insertHead(list,20);
	insertHead(list,30);
	insertHead(list,40);
	insertHead(list,50);
	insertHead(list,60);
	insertHead(list,70);
	insertHead(list,80);
	insertHead(list,90);
	listNode(list); 
	
	findNode(list,20);
	findNode(list,7);
	
	return 0;
}
