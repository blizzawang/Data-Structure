//栈的链式实现
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//结点结构
typedef struct Node{
	int data;//数据域
	struct Node *next;//指针域
}Node,*PNode;

//链栈结构
typedef struct{
	//链栈是限定在表头进行插入删除的链表，表头一端称为栈顶，表尾称为栈底
	PNode top;//栈顶指针
	int length;//链栈长度
}Stack,*PStack;

//链栈的初始化
Stack InitStack(){
	Stack s;
	//头指针初始无指向
	s.top = NULL;
	//链栈长度初始为0
	s.length = 0;
	return s;
}

//判断链栈是否为空
int StackEmpty(PStack s){
	if(s->length == 0)
		return 1;
	else
		return 0;
}

//链栈的入栈操作
int Push(PStack s,int val){
	//创建新结点
	PNode p = (PNode) malloc(sizeof(Node));
	if(p == NULL){
		exit(-1);
	}
	//为新结点的数据域赋值
	p->data = val;
	//结点入栈
	p->next = s->top;		//新结点指向栈顶结点
	s->top = p;				//栈顶指针后移
	s->length++;			//链栈长度加1
	return 1;
}

//链栈的出栈操作
int Pop(PStack s,int *val){
	//判断链栈是否空
	if(StackEmpty(s)){
		return 0;
	}
	//暂存栈顶结点
	PNode p = s->top;
	//取出删除结点元素值
	*val = p->data;
	//栈顶指针后移，指向下一个结点
	s->top = p->next;
	//释放结点p的内存
	free(p);
	//链栈长度减1
	s->length--;
	return 1;	//出栈成功，返回1
}

//链栈的销毁
void DestroyStack(PStack s){
	PNode p,q;
	//p初始指向栈顶结点
	p = s->top;
	while(p != NULL){
		q = p->top;		//q暂存p的下一个结点			
		free(p)；		//释放结点p的内存
		p = q;			//将q赋值给p
	}
}

//清空链栈
void ClearStack(PStack s){
	PNode p,q;
	//p初始指向栈顶结点
	p = s->top;
	while(p != NULL){
		q = p->top;		//q暂存p的下一个结点			
		free(p)；		//释放结点p的内存
		p = q;			//将q赋值给p
	}
	//栈顶指针最后无指向
	s->top = NULL;
}

int main(int argc, char const *argv[]){
	int i,val;
	//初始化链栈
	Stack s = InitStack();
	if(StackEmpty(&s)){
		printf("链栈为空\n");
	}
	//元素入栈
	Push(&s,1);
	Push(&s,2);
	Push(&s,3);
	Push(&s,4);
	Push(&s,5);
	//元素出栈
	for(i = 0;i < 5;i++){
		Pop(&s,&val);
		printf("出栈元素为:%d\t",val);
	}
	return 0;
}