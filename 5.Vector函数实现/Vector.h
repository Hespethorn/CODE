#ifndef VECTOR_H
#define VECTOR_H
#define DEFAULT_CAPACITY 10
// 使用别名来命名元素类型，如果未来需要改变元素类型，只需修改这个别名即可。
// 这么做提升代码的可维护性和扩展性,这实际上是模拟了C++的泛型编程
typedef int ElemType;

typedef struct {
    ElemType *table;   // 指向堆空间的数组
    int  size;   // 元素的个数
    int  capacity; // 数组的容量
}Vector;

// 初始化一个Vector动态数组
Vector *create_Vector(void);

// 销毁一个Vector动态数组，释放内存。
void vector_destroy(Vector *v);

// 向动态数组末尾添加一个元素
void vector_push_back(Vector *v, ElemType val);

// 在动态数组最前面添加元素，所有元素依次后移
void vector_push_front(Vector *v, ElemType val);

// 将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector *v, int idx, ElemType val);

// 遍历打印整个Vector动态数组
void vector_print(Vector *v);

#endif // !VECTOR_H 保护头文件，防止多次定义