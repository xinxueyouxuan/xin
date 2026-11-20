#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int Type;
typedef struct{
	Type data[MAX];
	int front;
	int rear;
}Queue;

//队列初始化 
void initQueue(Queue *Q){
	Q->front = 0;
	Q->rear = 0;
}

//判断队列是否为空
int isEmpty(Queue *Q){
 	if(Q->front == Q->rear){
 		printf("队列是空的\n");
 		return 1;
	}
	else
	 	return 0;
}

//出队
Type dequeue(Queue *Q){
	if(Q->front == Q->rear){
		printf("\n");
		return 0;
	}
	Type e = Q->data[Q->front];
	Q->front++;
	return e;
}

//队尾满了，调整队列
int queueFull(Queue *Q){
	if(Q->front > 0){
		int step = Q->front;
		int i;
		//将队列往前挪step位 
		for(i=Q->front;i<Q->rear;i++){
			Q->data[i - step] = Q->data[i];
		}
		Q->front = 0;
		Q->rear = Q->rear - step;
		return 1;
	}
	else{
		printf("队列已经满了\n");
		return 0;
	}
}

//入队
int equeue(Queue *Q,Type e){
	if(Q->rear >= MAX){
		if(!queueFull(Q)){
			return 0;
		}
	}
	Q->data[Q->rear] = e;
	Q->rear++;
	return 1;
}

//获取队头数据
int getHead(Queue *Q,Type *e){
	if(Q->front == Q->rear){
		printf("队列是空的\n");
		return 0;
	}
	*e = Q->data[Q->front];
	return 1;
}

int main(){
	Queue Q;
	initQueue(&Q);
	isEmpty(&Q);
	
	equeue(&Q,10);
	equeue(&Q,20);
	equeue(&Q,30);
	equeue(&Q,40);
	equeue(&Q,50);
	isEmpty(&Q);
	
	int e;
	getHead(&Q,&e);
	printf("getHead-->e=%d\n",e);
	 
	return 0;
} 
