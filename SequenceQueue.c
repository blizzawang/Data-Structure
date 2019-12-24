//队列的顺序实现
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 10

typedef struct {
	//顺序队列是只允许在后端插入，在前端删除的顺序表，后端称为队尾，前端称为队头
	int *data;//动态数组
	int front;//队头指针
	int rear;//队尾指针
}Queue,*PQueue;

//顺序队列的初始化
Queue InitQueue(){
	Queue q;
	//分配数组内存
	q.data = (int*) malloc(sizeof(int) * MAXSIZE);
	if(q.data == NULL){
		exit(-1);
	}
	//队头和队尾指针初始为0
	q.front = q.rear = 0;
	return q;
}

//判断顺序队列是否满
int QueueFull(PQueue q){
	if(q->rear == MAXSIZE)
		return 1;
	else
		return 0;		
}

//判断顺序队列是否为空
int QueueEmpty(PQueue q){
	if(q->front == q->rear)
		return 1;
	else
		return 0;		
}

//顺序队列的入队操作
int EnQueue(PQueue q,int val){
	//判断当前顺序队列是否满
	if(QueueFull(q)){
		return 0;
	}
	//元素入队
	q->data[q->rear] = val;	//[0]1 [1]2 [2]3 [3]4 [4]5
	//队尾指针加1
	q->rear++;
	return 1;//入队成功，返回1
}

//顺序队列的出队操作
int DeQueue(PQueue q,int *val){
	//判断当前顺序队列是否空
	if(QueueEmpty(q)){
		return 0;
	}
	//取出元素值
	*val = q->data[q->front];
	//队头指针后移
	q->front++;
	return 1;//出队成功，返回1
}

//顺序队列的销毁
void DestroyQueue(PQueue q){
	if(q->data != NULL){
		//释放数组内存
		free(q->data);
	}
	q->front = q->rear = 0;
}

//清空顺序队列
void ClearQueue(PQueue q){
	//清空顺序队列无需释放数组内存
	q->front = q->rear = 0;		//将队头和队尾指针重置即可
}

int main(int argc, char const *argv[]){
	int i,val;
	//初始化顺序队列
	Queue q = InitQueue();
	if(QueueEmpty(&q)){
		printf("队列为空\n");
	}
	//元素入队
	EnQueue(&q,1);
	EnQueue(&q,2);
	EnQueue(&q,3);
	EnQueue(&q,4);
	EnQueue(&q,5);
	EnQueue(&q,6);
	EnQueue(&q,7);
	EnQueue(&q,8);
	EnQueue(&q,9);
	EnQueue(&q,10);
	//元素出队
	for(i = 0;i < 10;i++){
		DeQueue(&q,&val);
		printf("出队元素为:%d\t",val);
	}
	return 0;
}