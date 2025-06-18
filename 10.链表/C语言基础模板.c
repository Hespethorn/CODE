#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void print_arr(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}


/*
插入排序 优化 : 用向后移动腾出插入位置, 然后插入实现插入排序
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
		print_arr(arr, len);    // 每一轮摸牌后查看排序后的数组
	}
}
int main(void) {
    printf("hello world!\n");
    return 0;
}