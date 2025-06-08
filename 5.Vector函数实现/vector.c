#include "Vector.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

// ��C������,static���κ�����ʾ�˺������ڵ�ǰ�ļ��ڲ���Ч
static void vector_resize(Vector *v) {
	ElemType *p2 = realloc(v->table, v->capacity * 2 * sizeof(ElemType));
	//�õ���������ʹ�����Ҫ�����ˣ����Ƕ����������˴�Ӧ����һ����ֵ��������ı����������
	if (p2 == NULL)
	{
		printf("ralloc failed in vector_resize vec->table ");
		return NULL;
	}
	//�ж�realloc�Ƿ�ɹ�
	v->table = p2;
	v->capacity *= 2;
}

// ��ʼ��һ��Vector��̬����
Vector *create_Vector() {
	Vector *vec = (Vector *)malloc(sizeof(Vector));
	if (vec == NULL) {
		printf("malloc failed in create_Vector");
	}
	//�����ڴ�
	vec->table = malloc(DEFAULT_CAPACITY * sizeof(ElemType));//10*ElemType ��С�ߴ������ DEFAULT_CAPACITY �궨��
	if (vec->table == NULL)
	{
		printf("malloc failed in create_Vector vec->table ");
		free(vec);
		return NULL;
	}
	vec->size = 0;       // ��ʼ��Ԫ��
	vec->capacity = DEFAULT_CAPACITY;
	return vec;
}

// ����һ��Vector��̬���飬�ͷ��ڴ档��ʵ����ģ����C++����������
void vector_destroy(Vector *v)
{
	free(v->table);//���ͷ�
	free(v);//���ͷ�
}

// ��̬����ĩβ���һ��Ԫ��
void vector_push_back(Vector *v, ElemType element)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//�ж��Ƿ���Ҫ����
	v->table[v->size] = element;
	v->size++;
	return 0;
}

// �ڶ�̬������ǰ�����Ԫ�أ�����Ԫ�����κ���
void vector_push_front(Vector *v, ElemType val)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//�ж��Ƿ���Ҫ����
	for (int i = v->size; i > 0; i--)
	{
		v->table[i] = v->table[i - 1];
	}
	v->table[0] = val;
	v->size++;
	return 0;
}

// ��Ԫ��val��ӵ�����Ϊidx��λ�ã�idx�����Ԫ�����κ���
void vector_insert(Vector *v, int idx, ElemType val)
{
	if (v->size == v->capacity) {
		vector_resize(v);
	}//�ж��Ƿ���Ҫ����

	for (int i = v->size; i > idx; i--)
	{
		v->table[i] = v->table[i - 1];
	}
	v->table[idx] = val;
	v->size++;
	return 0;
}

// ������ӡ����Vector��̬����
void vector_print(Vector *v)
{
	for (int i = 0; i < v->size; i++)
	{
		printf("%d\t", v->table[i]);
	}
}
