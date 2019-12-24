//栈的顺序实现
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define	MAXSIZE 10

typedef struct{
	//顺序栈是限定在表尾进行插入删除的线性表，表尾一端称为栈顶，表头称为栈底
	int *data;//动态数组
	int top;//栈顶指针
	int length;//顺序栈长度
}Stack,*PStack;

//初始化顺序栈
Stack InitStack(){
	Stack s;
	//分配数组内存
	s.data = (int*) malloc(sizeof(int) * MAXSIZE);
	if(s.data == NULL){
		exit(-1);
	}
	//栈顶指针初始为0
	s.top = 0;
	//顺序栈长度初始为0
	s.length = 0;
	return s;
}

//求顺序栈长度
int StackLength(Stack s){
	//返回length属性即可
	return s.length;
}

//判断顺序栈是否为空
int StackEmpty(PStack s){
	if(s->length == 0)
		return 1;
	else
		return 0;		
}

//判断顺序栈是否满
int StackPull(PStack s){
	if(s->length == MAXSIZE)
		return 1;
	else
		return 0;
}

//顺序栈的入栈操作
int Push(PStack s,int val){
	//判断当前顺序栈是否满
	if(StackPull(s)){
		return 0;
	}
	//元素入栈
	s->data[s->top] = val;
	//栈顶指针加1
	s->top++;
	//顺序栈长度加1
	s->length++;
	return 1;//入栈成功，返回1
}

//顺序栈的出栈操作
int Pop(PStack s,int *val){
	//判断当前顺序栈是否空
	if(StackEmpty(s)){
		return 0;
	}
	/*
		这里必须先让指针减1，因为元素入栈之后，栈顶指针指向的是栈顶元素的下一个位置
	*/
	//栈顶指针减1
	s->top--;
	//元素出栈
	*val = s->data[s->top];
	//顺序栈长度减1
	s->length--;
	return 1;//出栈成功，返回1
}

//清空顺序栈
void ClearStack(PStack s){
	//清空顺序栈，只需将栈顶指针置为0即可
	if(StackEmpty(s)){
		return;
	}
	s->top = 0;
	s->length = 0;
}

//销毁顺序栈
void DestroyStack(PStack s){
	//释放动态数组内存
	if(s->data == NULL){
		free(s->data);
	}
	s->top = 0;
	s->length = 0;
}

int main(int argc, char const *argv[]){	
	int i,val;
	//初始化顺序栈
	Stack s = InitStack();
	if(StackEmpty(&s)){
		printf("顺序栈为空\n");
	}
	//元素入栈
	Push(&s,1);
	Push(&s,2);
	Push(&s,3);
	Push(&s,4);
	Push(&s,5);
	printf("元素人栈后顺序栈长度为:%d\n", StackLength(s));
	//元素出栈
	for(i = 0;i < 5;i++){
		Pop(&s,&val);
		printf("出栈元素为:%d\n",val);
	}
	printf("元素出栈后顺序栈长度为:%d\n", StackLength(s));
}