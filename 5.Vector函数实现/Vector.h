#ifndef VECTOR_H
#define VECTOR_H
#define DEFAULT_CAPACITY 10
// ʹ�ñ���������Ԫ�����ͣ����δ����Ҫ�ı�Ԫ�����ͣ�ֻ���޸�����������ɡ�
// ��ô����������Ŀ�ά���Ժ���չ��,��ʵ������ģ����C++�ķ��ͱ��
typedef int ElemType;

typedef struct {
    ElemType *table;   // ָ��ѿռ������
    int  size;   // Ԫ�صĸ���
    int  capacity; // ���������
}Vector;

// ��ʼ��һ��Vector��̬����
Vector *create_Vector(void);

// ����һ��Vector��̬���飬�ͷ��ڴ档
void vector_destroy(Vector *v);

// ��̬����ĩβ���һ��Ԫ��
void vector_push_back(Vector *v, ElemType val);

// �ڶ�̬������ǰ�����Ԫ�أ�����Ԫ�����κ���
void vector_push_front(Vector *v, ElemType val);

// ��Ԫ��val��ӵ�����Ϊidx��λ�ã�idx�����Ԫ�����κ���
void vector_insert(Vector *v, int idx, ElemType val);

// ������ӡ����Vector��̬����
void vector_print(Vector *v);

#endif // !VECTOR_H ����ͷ�ļ�����ֹ��ζ���