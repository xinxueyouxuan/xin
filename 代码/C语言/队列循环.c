#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;

typedef struct{
	Type *data;
	int front;
	int rear;
}Queue;

Queue *initQueue0(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->data = (Type*)malloc(sizeof(Type)*MAX);
	q->front = 0;
	q->rear = MAX - 1;
	return q;
}

Queue *initQueue(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->data = (Type*)malloc(sizeof(Type)*MAX);
	q->front = 0;
	q->rear = 0;
	return q;
}

//入队 
int equeue0(Queue *Q,Type e){
	Q->rear = (Q->rear + 1) % MAX;
	if((Q->rear + 1)%MAX == Q->front){
		printf("队列已满\n");
		return 0;
	}
	Q->data[Q->rear] = e;
	return 1;
}

int equeue(Queue *Q,Type e){
	if((Q->rear + 1)%MAX == Q->front){
		printf("队列已满\n");
		return 0;
	}
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAX;
	return 1;
} 

//出队
int dequeue(Queue *Q,Type *e){
	if(Q->front == Q->rear){
		printf("队列为空\n");
		return 0;
	}
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAX;
	return 1;
} 

//获取队头元素
int getHead(Queue *Q,Type *e){
	if(Q->front == Q->rear){
		printf("队列为空\n");
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
} 

int main(){
	Queue *q = initQueue();
	
	equeue(q,10);
	equeue(q,20);
	equeue(q,30);
	equeue(q,40);
	equeue(q,50);
	equeue(q,60);
	
	Type e;
	
	getHead(q,&e);
	printf("getHead->e=%d\n",e);
	
	dequeue(q,&e);
	printf("dequeue->e=%d\n",e);
	dequeue(q,&e);
	printf("dequeue->e=%d\n",e);
	
	getHead(q,&e);
	printf("getHead->e=%d\n",e);
	
	
	
	return 0;
} 
