#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
	ElemType data;
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

//头插法
int insertHead(Node *L,ElemType e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	p->next = L->next;
	L->next = p;
	return 1;
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
Node *insertTail(Node *L,ElemType e){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = e;
	L->next = p;
	p->next = NULL;
	return p;
} 

//在指定位置插入
int insertNode(Node *L,int pos,ElemType e){
	Node *p = L;
	int i = 0;
	while(i < pos-1){
		p = p->next;
		i++;
		//防止没有此节点 
		if(p == NULL){
			return 0;
		}
	}
	
	Node *q = (Node*)malloc(sizeof(Node));
	q->data = e;
	q->next = p->next;
	p->next = q;
	return 1;
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

//删除节点 
int deleteNode(Node *L,int pos){
	Node *p = L;
	int i = 0;
	while(i < pos-1){
		p = p->next;
		i++;
		if(p == NULL){
			return 0;
		}
	}
	if(p->next == NULL){
		printf("错误\n");
		return 0;
	}
	//把q节点独立出来 
	Node *q = p->next;
	p->next = q->next;
	//清除q节点 
	free(q);
	return 1;
} 

//清空链表 
void freeNode(Node *L){
	Node *p = L->next;
	Node *q;
	
	while(p = NULL){
		q = p->next;
		free(q);
		p = q;
	}
	//仅保留头节点 
	L->next = NULL;
}

int main(){
	Node *list = initList();
	
	//头插法 
	insertHead(list,10);
	insertHead(list,20);
	insertHead(list,30);
	listNode(list);
	
	//尾插法 
	Node *tail = get_tail(list);
	tail = insertTail(tail,10);
	tail = insertTail(tail,20);
	tail = insertTail(tail,30);
	listNode(list);
	
	//在指定位置插入
	insertNode(list,4,15);
	listNode(list);
	
	//在指定位置删除节点
	deleteNode(list,3);
	listNode(list); 
	
	//释放链表 
	return 0;
} 
