//线性表的链式实现(循环链表)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node{
	int data;//数据域
	struct Node *next;//指针域
}Node,*List;

List InitList(){
	List l;
	//创建头结点，完成创建后可以将l看成尾结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = l;		//头结点指向它本身
	return l;
}

//头插法发创建循环链表
List CreateListH(int *num,int length){
	int i;
	List l,s;
	//创建头结点，完成创建后可以将l看成尾结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = l;		//头结点指向它本身	
	for(i = 0;i < length;i++){
		//创建新结点
		s = (List) malloc(sizeof(Node));
		if(s == NULL){
			exit(-1);
		}
		//为新结点的数据域赋值
		s->data = num[i];
		//头插法插入结点
		s->next = l->next;		//新结点指向头结点的下一个结点
		l->next = s;			//头结点指向新结点
	}
	return l;
}

//尾插法创建循环链表
List CreateListT(int *num,int length){
	int i;
	List l,s,t;
	//创建头结点，完成创建后可以将l看成尾结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	t = l;
	for(i = 0;i < length;i++){
		//创建新结点
		s = (List) malloc(sizeof(Node));
		if(s == NULL){
			exit(-1);
		}
		//为新结点的数据域赋值
		s->data = num[i];
		//尾插法插入结点
		t->next = s;			//尾结点指向新结点
		t = s;					//新结点成为尾结点
	}
	t->next = l;				//尾结点最终指向头结点
	return l;
}

void TraverseList(List l){
	//p指向首元结点
	List p = l->next;
	while(p != l){					//遍历结束条件:当前结点是否指向了头结点。若指向头结点，则遍历结束
		printf("%d\t",p->data);		//输出结点数据
		p = p->next;				//p指向下一个结点
	}
}

//循环链表其它操作与单链表相同
//合并两个循环链表
List ConnectList(List l1,List l2){	//l1、l2为对应循环链表的尾结点
	List p;
	//p指向l1的头结点
	p = l1->next;
	//让l1指向l2的首元结点，此时l2已经连接到l1的尾端
	l1->next = l2->next->next;
	free(l2->next);//释放l2的头结点
	l2->next = p;//l2指向l1的头结点，此时l2的尾端连接到l1的首端
	return l2;	//l2为新循环链表的尾结点

}

int main(int argc, char const *argv[]){
	List l,l2,l3;
	int num[] = {1,2,3,4,5};
	//创建循环链表
	l = CreateListH(num,5);
	//遍历循环链表
	printf("头插法创建的循环链表:");
	TraverseList(l);
	printf("\n");
	//创建循环链表
	l2 = CreateListT(num,5);
	//遍历循环链表
	printf("尾插法创建的循环链表:");
	TraverseList(l2);
	printf("\n");
	//合并两个循环链表
	l3 = ConnectList(l,l2);
	//遍历循环链表
	printf("合并后的循环链表:");
	TraverseList(l3);
	return 0;
}