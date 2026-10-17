#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;

typedef struct QueueNode{
	Type data;
	struct QueueNode *next;
}QueueNode;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
}Queue;

//队列的链式结构-初始化
Queue *initQueue(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	
	node->data = 0;
	node->next = NULL;
	
	q->front = node;
	q->rear = node;
	
	return q;
}

//判断是否为空
int isEmpty(Queue *q){
	if(q->front == q->rear){
		return 1;
	}
	else
		return 0;
}

//入队
void equeue(Queue *q,Type e){
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
	node->data = e;
	node->next = NULL;
	q->rear->next = node;
	q->rear = node;
}

//出队
int dequeue(Queue *q,Type *e){
	QueueNode *node = q->front->next;
	*e = node->data;
	q->front->next = node->next;
	if(q->rear == node){
		q->rear = q->front;
	}
	free(node);
	return 1;
}

//获取队头元素
Type getHead(Queue *q){
	if(isEmpty(q)){
		printf("队列为空\n");
		return 0;
	}
	return q->front->next->data;
} 

int main(){
	Queue *q = initQueue();
	
	equeue(q,10);
	equeue(q,20);
	equeue(q,30);
	equeue(q,40);
	equeue(q,50);
	
	Type e;
	
	e = getHead(q);
	printf("getHead->e=%d\n",e);
	
	dequeue(q,&e);
	printf("dequeue->e=%d\n",e);
	
	e = getHead(q);
	printf("getHead->e=%d\n",e);
	
	return 0;
}
