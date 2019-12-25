//队列的链式实现
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//结点结构
typedef struct Node{
	int data;
	struct Node *next;
}Node,*PNode;

//链式队列结构
typedef struct{
	PNode front;//队头指针
	PNode rear;//队尾指针
}Queue,*PQueue;

//链式队列的初始化
Queue InitQueue(){
	Queue q;
	PNode p;
	//创建头结点
	p = (PNode) malloc(sizeof(Node));
	if(p == NULL){
		exit(-1);
	}
	//头结点初始无指向
	p->next = NULL;
	//初始队头和队尾指针均指向头结点
	q.front = q.rear = p;
	return q;
}

//判断链式队列是否为空
int QueueEmpty(PQueue q){
	//若队头和队尾指针重合，则表示链式队列为空
	if(q->front == q->rear)
		return 1;
	else
		return 0;
}

//链式队列的入队操作
void Push(PQueue q,int val){
	//链式队列没有满的情况
	//创建新结点
	PNode p = (PNode) malloc(sizeof(Node));
	if(p == NULL){
		exit(-1);
	}
	//为新结点的数据域赋值
	p->data = val;
	//结点入队
	p->next = NULL;		//队尾结点指针域无指向
	q->rear->next = p;	//队尾指针指向新结点
	q->rear = p;		//新结点成为队尾结点
}

//链式队列的出队操作
int Pop(PQueue q,int *val){
	PNode p;
	//判断当前链式队列是否为空
	if(QueueEmpty(q)){
		return 0;
	}
	//结点出队
	p = q->front->next;				//p指向头结点的下一个结点
	*val = p->data;					//保存出队结点的数据
	q->front->next = p->next;		//队头指针指向出队结点的下一个结点
	free(p);						//释放出队结点内存
	return 1;						//出队成功，返回1
}

//链式队列的销毁
void DestroyQueue(PQueue q){
	//销毁链队中的所有结点内存	
	PNode p,q;
	p = q->front;				//保存队列的头结点
	while(p != NULL){
		q = p->next;			//q保存头结点的下一个结点
		free(p);				//释放p的内存
		p = q;					//将q赋值给p
	}
}

//清空链式队列
void ClearQueue(PQueue q){
	if(QueueEmpty(q)){
		return;
	}
	//清空除头结点外的所有结点内存
	PNode p,q;
	q->rear = q->front;			//队尾指针指向队头
	p = q->front->next;			//保存队列的首元结点
	q->front->next = NULL;		//头结点指针域置为NULL
	while(p != NULL){
		q = p->next;			//q保存头结点的下一个结点
		free(p);				//释放p的内存
		p = q;					//将q赋值给p
	}
}

int main(int argc, char const *argv[]){
	int i,val;
	//初始化链式队列
	Queue q = InitQueue();
	//结点入队
	Push(&q,1);
	Push(&q,2);
	Push(&q,3);
	Push(&q,4);
	Push(&q,5);
	//结点出队
	for(i = 0;i < 5;i++){
		Pop(&q,&val);
		printf("出队结点元素值为:%d\t",val);
	}
	return 0;
}