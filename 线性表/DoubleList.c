//线性表的链式实现(双链表)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node{
	int data;//数据域
	struct Node *prior;//前驱指针
	struct Node *next;//后继指针
}Node,*List;

//初始化双链表
List InitList(){
	//创建头结点
	List l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = l->prior = NULL;		//初始前驱和后继指针均无指向
	return l;
}

//头插法创建双链表
List CreateListH(int *num,int length){
	int i;
	List l,s;
	//创建头结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	l->next = l->prior = NULL;		//初始前驱和后继指针均无指向
	for(i = 0;i < length;i++){
		//创建新结点
		s = (List) malloc(sizeof(Node));
		//为新结点的数据域赋值
		s->data = num[i];
		//头插法插入结点
		s->next = l->next;			//新结点的后继指向头结点的下一个结点
		if(l->next != NULL){		//判断当前l是否为头结点，若l为头结点，则不需处理头结点的后续结点指针
			//此时l不为头结点，所以还需处理头结点的后续结点指针
			l->next->prior = s;		//头结点的下一个结点的前驱指针指向新结点
		}
		l->next = s;				//头结点的后继指向新结点
		s->prior = l;				//新结点的前驱指向头结点
	}
	return l;
}

//尾插法创建双链表
List CreateListT(int *num,int length){
	int i;
	List l,t,s;
	//创建头结点
	l = (List) malloc(sizeof(Node));
	if(l == NULL){
		exit(-1);
	}
	t = l;		//尾结点t初始指向头结点
	for(i = 0;i < length;i++){
		//创建新结点
		s = (List) malloc(sizeof(Node));
		if(s == NULL){
			exit(-1);
		}
		//为新结点的数据域赋值
		s->data = num[i];
		//尾插法插入结点
		t->next = s;			//尾结点的后继指向新结点
		s->prior = t;			//新结点的前驱指向尾结点
		t = s;					//新结点成为尾结点
	}
	return l;
}

//遍历双链表
void TraverseList(List l){
	//p指向首元结点
	List p = l->next;
	while(p != NULL){
		printf("%d\t", p->data);
		p = p->next;	//p指向下一个结点
	}
}

//求双链表的长度
int ListLength(List l){
	int length = 0;
	//p指向首元结点
	List p = l->next;
	while(p != NULL){
		length++;
		p = p->next;	//p指向下一个结点
	}
	return length;
}

//判断双链表是否为空
int ListEmpty(List l){
	if(l->next == NULL)
		return 1;
	else
		return 0;
}

//双链表的插入操作
int InsertList(List l,int pos,int val){
	List p,s;
	int i = 0,length;
	//p指向头结点
	p = l;
	//获得当前双链表的长度
	length = ListLength(l);
	//判断pos值的合法性
	//链表不存在满的情况
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
	//在插入结点之前，找到插入位置的前一个结点
	while(i < pos - 1 && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为插入位置的前一个结点
	s->next = p->next;			//新结点的后继指向p的下一个结点
	//此时需要讨论p是否为尾结点
	/*
		若p为尾结点，则无需考虑p的后继结点的指针问题
		若p不为尾结点，则还需考虑p的后继结点的前驱指针的指向
	*/
	if(p->next != NULL){
		p->next->prior = s;		//p的下一个结点的前驱指向新结点
	}
	p->next = s;				//p的后继指向新结点
	s->prior = p;				//新结点的前驱指向p
	return 1;					//插入成功，返回1
}

//双链表的删除操作
int DeleteList(List l,int pos,int *val){
	List p,q;
	int length;
	int i = 0;
	//p初始指向头结点
	p = l;
	//获得当前双链表的长度
	length = ListLength(l);
	//判断pos值的合法性
	//判断当前双向链表是否为空
	if(pos < 1 || pos > length){
		return 0;
	}
	//在删除结点之前，找到删除位置的前一个结点
	while(i < pos - 1 && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为删除位置的前一个结点
	q = p->next;		//q为删除位置结点
	//保存删除结点的元素值
	*val = q->data;
	//删除结点
	p->next = q->next;		//p的后继指向q的下一个结点，即:跳过结点q
	/*
		此时需要讨论当前的p是否为尾结点
		若p为尾结点，则无需考虑p的前驱指针指向
		若p不为尾结点，则还需考虑p的前驱指针指向
	*/
	if(p->next != NULL){
		p->next->prior = p;		//q的前驱指向新结点
	}
	free(q);					//释放结点q的内存
	return 1;					//删除成功，返回1
}

//双链表的查找(按址查找)
int GetElem(List l,int pos){
	List p;
	int i = 0,length;
	//获得当前双链表的长度
	length = ListLength(l);
	//p初始指向头结点
	p = l;
	//判断pos值的合法性
	//判断当前双链表是否为空
	if(pos < 1 || pos > length || ListEmpty(l)){
		return 0;
	}
	//找到pos位置的结点
	while(i < pos && p != NULL){
		i++;
		p = p->next;		//p指向下一个结点
	}
	//此时p为要查找的结点
	return p->data;			//返回结点数据
}

//双链表的查找(按值查找)
int GetLocate(List l,int val){
	int index = 1;
	//p初始指向首元结点
	List p = l->next;
	//判断当前双链表是否为空
	if(ListEmpty(l)){
		return 0;
	}
	//遍历双链表，查找指定元素值的结点位置
	while(p != NULL && p->data != val){
		index++;
		p = p->next;		//p指向下一个结点
	}
	/*
		此时有两种情况:
			1、查找成功，返回index即可
			2、查找失败，此时p为NULL
	*/
	if(p == NULL)
		return 0;
	else
		return index;
}

//双链表的销毁
void DestroyList(List l){
	List p,q;
	//p指向头结点
	p = l;
	while(p != NULL){
		q = p->next;	//q暂时保存p的下一个结点
		free(p);		//释放结点p的内存
		p = q;			//将q赋值给p
	}
}

//清空双链表
void ClearList(List l){
	//释放除头结点外的所有结点内存
	List p,q;
	//p初始指向首元结点
	p = l->next;
	while(p != NULL){
		q = p->next;	//q暂时保存p的下一个结点
		free(p);		//释放结点p
		p = q;			//q赋值给p
	}
	l->next = NULL;		//头结点指针域无指向
}

int main(int argc, char const *argv[]){
	List l,l2,l3;
	int num[] = {1,2,3,4,5};
	int i,val;
	//创建双链表
	l = CreateListT(num,5);
	//遍历双链表
	printf("尾插法创建的双链表:");
	TraverseList(l);
	printf("\n");
	//创建双链表
	l2 = CreateListH(num,5);
	//遍历双链表
	printf("头插法创建的双链表:");
	TraverseList(l2);
	printf("\n");
	l3 = InitList();
	if(ListEmpty(l3)){
		printf("双链表l3为空\n");
	}
	//求双链表的长度
	printf("双链表l的长度为:%d\n",ListLength(l));
	//插入5个结点
	for(i = 10;i < 15;i++){
		InsertList(l,1,i);
	}
	//遍历双链表
	printf("插入结点后的双链表:");
	TraverseList(l);
	printf("\n");
	//删除5个结点
	for(i = 0;i < 5;i++){
		DeleteList(l,1,&val);
		printf("删除的结点元素值为:%d\t",val);
	}
	//遍历双链表
	printf("删除结点后的双链表:");
	TraverseList(l);
	printf("\n");
	//按址查找
	printf("第一个位置上的结点数据为:%d\n",GetElem(l,1));
	//按值查找
	printf("元素值为1的结点位置为:%d\n",GetLocate(l,1));
	return 0;
}