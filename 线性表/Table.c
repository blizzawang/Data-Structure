//线性表的顺序实现
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAXSIZE 10

typedef struct {
	int* head;		//动态数组
	int size;		//顺序表的总大小
	int length;		//顺序表的长度，即:当前顺序表的有效元素个数
}Table;

//初始化顺序表
void InitTable(Table *t){
	//创建动态数组
	t->head = (int*) malloc(sizeof(int) * MAXSIZE);
	if(t->head == NULL){
		exit(-1);
	}
	t->size = MAXSIZE;	//顺序表的总大小为MAXSIZE
	t->length = 0;		//当前为空表，长度为0
}

//求顺序表的长度
int TableLength(Table *t){
	//顺序表的长度即为length属性值
	return t->length;
}

//判断顺序表是否为空
int TableEmpty(Table *t){
	if(t->length == 0)
		return 1;
	else
		return 0;
}

//判断顺序表是否已满
int TableFull(Table *t){
	//若当前顺序表长度等于顺序表的最大容量，则表示满
	if(t->length == t->size)
		return 1;
	else
		return 0;
}

//遍历顺序表
void TraverseTable(Table *t){
	int i;
	//判断当前顺序表是否为空
	if(TableEmpty(t)){
		printf("顺序表为空\n");
	}else{
		//遍历顺序表
		for(i = 0;i < t->length;i++){
			printf("%d\t", t->head[i]);
		}
		printf("\n");
	}
}

//顺序表的插入
int InsertTable(Table *t,int pos,int val){
	int i;
	//判断pos值的合法性
	//判断当前顺序表是否已满
	if(pos < 1 || pos > t->length + 1 || TableFull(t)){//若顺序表长度等于顺序表最大容量，表示表满
		return 0;
	}
	//插入元素前，需将插入位置后面的元素都向后移动一位
	/*
		举个例子:在序列1 2 3 4 5中，若想在位置3插入元素，则需将3 4 5往后移动一位
		即:从下标pos - 1开始，到最后一个元素为止，均向后移动一位
	*/
	for(i = t->length - 1;i >= pos - 1;--i){//i的初始值为t->length-1，使得若插入的位置为表尾，则循环不执行，直接插入元素
		//元素后移
		t->head[i + 1] = t->head[i];
	}
	//插入元素
	t->head[pos - 1] = val;
	//长度加1
	t->length++;
}

//顺序表的删除
int DeleteTable(Table *t,int pos,int *val){
	int i;
	//判断pos值的合法性
	//判断当前顺序表是否已空
	if(pos < 1 || pos > t->length || TableEmpty(t)){
		return 0;
	}
	//删除元素时，需将删除位置后面的元素都向前移动一位
	/*
		举个例子:在序列1 2 3 4 5中，若想在位置3删除元素，则需将4 5往前移动一位
		即:从下标pos开始，到最后一个元素为止，均向前移动一位
	*/
	//先保存待删除的元素值
	*val = t->head[pos - 1];
	for(i = pos;i < t->length;i++){//i的初始值为pos，使得若删除的位置为表尾，则循环不执行，直接删除元素	
		//元素前移
		t->head[i - 1] = t->head[i];
	}
	//完成删除，长度减1
	t->length--;
	return 1;//删除成功，返回1
}

//顺序表的查找(按址查找)
int GetElem(Table *t,int pos){
	//判断pos值的合法性
	//判断当前顺序表是否为空
	if(pos < 1 || pos > t->length || TableEmpty(t)){
		return 0;
	}
	//返回指定位置的元素值
	return t->head[pos - 1];
}

//顺序表的查找(按值查找)
int GetLocate(Table *t,int val){
	int i;
	//判断当前顺序表是否为空
	if(TableEmpty(t)){
		return 0;
	}
	//遍历顺序表查找指定值的位置
	for(i = 0;i < t->length - 1;i++){
		if(t->head[i] == val){
			return i + 1;//返回元素位置
		}
	}
	return 0;//查找失败，返回0
}

//顺序表的销毁
void DestroyTable(Table *t){
	//销毁数组内存
	free(t->head);
	//顺序表长度清零
	t->length = 0;
}

//清空顺序表
void ClearTable(Table *t){
	//顺序表长度清零
	t->length = 0;
}

int main(int argc, char const *argv[]){
	int i,val;
	Table t;
	//初始化顺序表
	InitTable(&t);
	//求顺序表长度
	printf("顺序表的长度为:%d\n", TableLength(&t));
	//判断顺序表是否为空
	if(TableEmpty(&t)){
		printf("顺序表为空\n");
	}else{
		printf("顺序表不为空\n");
	}
	//插入10个元素
	InsertTable(&t,1,1);
	InsertTable(&t,2,2);
	InsertTable(&t,3,3);
	InsertTable(&t,4,4);
	InsertTable(&t,5,5);
	InsertTable(&t,6,6);
	InsertTable(&t,7,7);
	InsertTable(&t,8,8);
	InsertTable(&t,9,9);
	InsertTable(&t,10,10);
	//遍历顺序表
	printf("插入元素后:");
	TraverseTable(&t);
	//删除5个元素
	for(i = 1;i <= 5;i++){
		DeleteTable(&t,1,&val);
		printf("删除元素:%d\t",val);
	}
	printf("\n");
	//遍历顺序表
	printf("删除元素后:");
	TraverseTable(&t);
	//按址查找
	printf("第一个位置上的元素值为:%d\n",GetElem(&t,1));;
	//按值查找
	printf("元素值6的位置为:%d\n",GetLocate(&t,6));
	return 0;
}