#include"sort.h"

int main(void) {
	int arr[] = { 1, 21, 45, 231, 99, 2, 18, 7, 4, 9 };
	int len = ARR_SIZE(arr);
	insertion_sort(arr, len);
	return 0;
}