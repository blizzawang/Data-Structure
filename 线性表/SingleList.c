//线性表的链式实现(单链表)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node{
	int data;//数据域
	struct Node *next;//指针域
}Node,*List;

//初始化单链表
List InitList(){
	//创建头结点
	List l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = NULL;//头结点初始无指向
	return l;
}

//头插法创建单链表
List CreateListH(int *num,int length){
	int i;
	List l,s;
	//创建头结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = NULL;//头结点初始无指向
	for(i = 0;i < length;i++){
		//创建新结点
		s = (List) malloc(sizeof(Node));
		if(s == NULL){
			exit(-1);
		}
		s->data = num[i];
		//头插法插入新结点
		s->next = l->next;	//新结点指向头结点的下一个结点
		l->next = s;		//头结点指向新结点
	}
	return l;//返回头结点
}

//尾插法创建单链表
List CreateListT(int *num,int length){
	List l,t,s;
	//创建头结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	//尾结点初始指向头结点
	t = l;
	for (int i = 0; i < length; ++i){
		s = (List) malloc(sizeof(Node));
		if(s == NULL){
			exit(-1);
		}
		//为结点的数据域赋值
		s->data = num[i];
		//尾插法插入新结点
		t ->next = s;		//尾结点指向新结点
		t = s;				//新结点成为尾结点
	}
	t->next = NULL;			//尾结点的指针域为NULL
	return l;
}


//遍历单链表
void TraverseList(List l){
	//p指向首元结点
	List p = l->next;
	while(p != NULL){
		printf("%d\t", p->data);	//输出数据
		p = p->next;				//p指向下一个结点
	}
}

//判断单链表是否为空
int ListEmpty(List l){
	//如果头结点无指向，证明单链表为空
	if(l->next == NULL)
		return 1;
	else
		return 0;
}

//求单链表的长度
int ListLength(List l){
	int length = 0;
	//p为首元结点
	List p = l->next;
	while(p != NULL){
		length++;		//长度加1
		p = p->next;	//p指向下一个结点
	}
	return length;
}

//单链表的插入操作
int InsertList(List l,int pos,int val){
	int i = 0,length;
	List s,p;
	p = l;		//p指向头结点
	length = ListLength(l);
	//获得当前单链表的长度
	//判断pos值的合法性
	//链表无需考虑满的情况
	if(pos < 1 || pos > length + 1){
		return 0;
	}
	//创建新结点
	s = (List) malloc(sizeof(Node));
	if(s == NULL){
		exit(-1);
	}
	//为新结点的数据域赋值
	s->data = val;
	//在插入新结点之前，需要找到插入位置的前一个结点，因为结点的插入会影响插入位置的前一个结点的指针
	//即:找到pos - 1的位置结点
	while(i < pos - 1 && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为插入位置的前一个结点
	//开始插入结点
	s->next = p->next;		//新结点指向p的下一个结点
	p->next = s;			//p指向新结点
	return 1;				//插入成功，返回1	
}

//单链表的删除操作
int DeleteList(List l,int pos,int *val){
	int i = 0,length;
	List p,q;
	length = ListLength(l);
	//判断pos值的合法性
	//判断当前单链表是否为空
	if(pos < 1 || pos > length || ListEmpty(l)){
		return 0;
	}
	//在删除结点之前，需要找到删除位置的前一个结点
	while(i < pos - 1 && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为当前结点的前一个结点
	q = p->next;			//q为p的下一个结点，即:删除位置的结点
	//保存待删除结点的数据
	*val = q->data;
	p->next = q->next;		//p指向q的下一个结点，即:跳过结点q
	free(q);				//释放结点q的内存
	return 1;				//删除成功，返回1
}

//单链表的查找(按址查找)
int GetElem(List l,int pos){
	int i = 0;
	List p = l;//p指向头结点
	//判断当前单链表是否为空
	if(ListEmpty(l)){
		return 0;
	}
	//查找pos位置的结点
	while(i < pos && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为查找位置的结点
	return p->data;			//返回结点数据
}

//单链表的查找(按值查找)
int GetLocate(List l,int val){
	int index = 0;
	List p = l;				//p指向头结点
	//遍历单链表，对每个数据进行匹配
	while(p != NULL && p->data != val){
		index++;
		p = p->next;		//p指向下一个结点
	}
	/*
		退出循环有两种可能:
			1、未找到，此时p为NULL
			2、已找到
	*/
	if(p == NULL)
		return 0;
	else
		return index;
}

//清空单链表
void ClearList(List l){
	//清空单链表要释放其它所有结点内存，而只留下头结点
	List p,q;
	p = l->next;		//p初始指向首元结点
	while(p != NULL){
		q = p->next;	//q存放p的下一个结点，否则释放了结点p的内存之后，p后面的结点就无法找到了
		free(p);		//释放结点p的内存
		p = q;			//将q赋值给p，q只起一个暂存的作用
	}
	l->next = NULL;		//将头结点指针域置为NULL
}

//销毁单链表
void DestroyList(List l){
	//释放单链表要释放所有结点的内存，包括头结点
	List p,q;
	p = l;
	while(p != NULL){
		q = p->next;	//变量p起一个暂存的作用，暂时存放下一个结点
		free(p);		//释放结点p的内存
		p = q;			//将q赋值给p
	}
}

int main(int argc, char const *argv[]){
	int num[] = {1,2,3,4,5};
	int i,val;
	List l,l2,l3;
	//初始化单链表
	l3 = InitList();
	if(ListEmpty(l3)){
		printf("单链表链l3为空\n");
	}
	//创建单链表
	l2 = CreateListH(num,5);
	//遍历单链表
	printf("头插法创建的单链表:");
	TraverseList(l2);
	printf("\n");
	//创建单链表
	l = CreateListT(num,5);
	//遍历单链表
	printf("尾插法创建的单链表:");
	TraverseList(l);
	printf("\n");
	//单链表l的长度
	printf("单链表l的长度为:%d\n", ListLength(l));
	//插入5个结点
	for(i = 10;i < 15;i++){
		InsertList(l,1,i);
	}
	//遍历单链表
	printf("插入结点后的单链表:");
	TraverseList(l);
	printf("\n");
	//删除5个结点
	for(i = 0;i < 5;i++){
		DeleteList(l,1,&val);
		printf("删除的结点数据为:%d\t",val);
	}
	//遍历单链表
	printf("删除结点后的单链表:");
	TraverseList(l);
	printf("\n");
	//按址查找
	printf("第一个位置上的元素为:%d\n",GetElem(l,1));
	//按值查找
	printf("元素值为1的结点位置为:%d\n",GetLocate(l,1));
	return 0;
}