#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Vector.h"

int main(void) {
	Vector *vec = create_Vector();
	// 测试尾部插入功能
	printf("尾部插入 1-5...\n");
	for (int i = 1; i <= 15; i++) {
		vector_push_back(vec, i);
	}
	vector_print(vec);
	// 测试头部插入功能
	printf("\n头部插入element 0...\n");
	vector_push_front(vec, 0);
	vector_print(vec);
	// 测试中间插入功能
	printf("\n特定位置插入 100 at index 3...\n");
	vector_insert(vec, 3, 100);
	vector_print(vec);
	// 销毁Vector，释放内存
	vector_destroy(vec);
	return 0;
}