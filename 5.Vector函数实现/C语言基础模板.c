#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Vector.h"

int main(void) {
	Vector *vec = create_Vector();
	// ����β�����빦��
	printf("β������ 1-5...\n");
	for (int i = 1; i <= 15; i++) {
		vector_push_back(vec, i);
	}
	vector_print(vec);
	// ����ͷ�����빦��
	printf("\nͷ������element 0...\n");
	vector_push_front(vec, 0);
	vector_print(vec);
	// �����м���빦��
	printf("\n�ض�λ�ò��� 100 at index 3...\n");
	vector_insert(vec, 3, 100);
	vector_print(vec);
	// ����Vector���ͷ��ڴ�
	vector_destroy(vec);
	return 0;
}