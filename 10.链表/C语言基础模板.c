#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void print_arr(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}


/*
�������� �Ż� : ������ƶ��ڳ�����λ��, Ȼ�����ʵ�ֲ�������
*/

void insertion_sort(int arr[], int len) {
	for (int i = 1; i < len; i++) {
		if (arr[i] < arr[i - 1]) {
			for (int j = i - 1; j >= 0; j--) {
				if (arr[i] < arr[j]) {
					SWAP(arr, i, j);
					i = j;
				}
			}
		}
		print_arr(arr, len);    // ÿһ�����ƺ�鿴����������
	}
}
int main(void) {
    printf("hello world!\n");
    return 0;
}