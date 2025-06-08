#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// 在C语言中,static修饰函数表示此函数仅在当前文件内部生效
static void vector_resize(Vector *v) {
	ElemType *p2 = realloc(v->table, v->capacity * 2 * sizeof(ElemType));
	//用到这个函数就代表需要扩容了，考虑二倍递增（此处应该有一个阈值，超过后改变递增倍数）
	if (p2 == NULL)
	{
		printf("ralloc failed in vector_resize vec->table ");
		return NULL;
	}
	//判断realloc是否成功
	v->table = p2;
	v->capacity *= 2;
}

// 初始化一个Vector动态数组
Vector *create_Vector() {
	Vector *vec = (Vector *)malloc(sizeof(Vector));
	if (vec == NULL) {
		printf("malloc failed in create_Vector");
	}
	//申请内存
	vec->table = malloc(DEFAULT_CAPACITY * sizeof(ElemType));//10*ElemType 大小尺寸的数组 DEFAULT_CAPACITY 宏定义
	if (vec->table == NULL)
	{
		printf("malloc failed in create_Vector vec->table ");
		free(vec);
		return NULL;
	}
	vec->size = 0;       // 初始无元素
	vec->capacity = DEFAULT_CAPACITY;
	return vec;
}

// 销毁一个Vector动态数组，释放内存。这实际上模拟了C++的析构函数
void vector_destroy(Vector *v)
{
	free(v->table);//先释放
	free(v);//后释放
}

// 向动态数组末尾添加一个元素
void vector_push_back(Vector *v, ElemType element)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//判断是否需要扩容
	v->table[v->size] = element;
	v->size++;
	return 0;
}

// 在动态数组最前面添加元素，所有元素依次后移
void vector_push_front(Vector *v, ElemType val)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//判断是否需要扩容
	for (int i = v->size; i > 0; i--)
	{
		v->table[i] = v->table[i - 1];
	}
	v->table[0] = val;
	v->size++;
	return 0;
}

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector *v, int idx, ElemType val)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//判断是否需要扩容

	for (int i = v->size; i > idx; i--)
	{
		v->table[i] = v->table[i - 1];
	}
	v->table[idx] = val;
	v->size++;
	return 0;
}

// 遍历打印整个Vector动态数组
void vector_print(Vector *v)
{
	for (int i = 0; i < v->size; i++)
	{
		printf("%d\t", v->table[i]);
	}
}
