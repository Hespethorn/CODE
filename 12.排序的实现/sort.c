#include"sort.h"

void print_arr(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void shell_sort(int arr[], int n) {
	int gap = n >> 1;
	while (gap > 0) {
		for (int i = gap; i < n; i = i + gap) {
			if (arr[i] < arr[i - gap]) {
				for (int j = i - gap; j >= 0; j = j - gap) {
					if (arr[i] < arr[j]) {
						SWAP(arr, i, j);
						i = j;
					}
					else {
						break;
					}
				}
			}
		}
		print_arr(arr, n);
		gap = gap >> 1;
	}
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

/*
希尔排序，特点一次多个排序，逐渐减小间隔。
*/

void shell_sort(int arr[], int n) {
	int gap = n >> 1;
	while (gap > 0) {
		for (int i = gap; i < n; i = i + gap) {
			if (arr[i] < arr[i - gap]) {
				for (int j = i - gap; j >= 0; j = j - gap) {
					if (arr[i] < arr[j]) {
						SWAP(arr, i, j);
						i = j;
					}
					else {
						break;
					}
				}
			}
		}
		print_arr(arr, n);
		gap = gap >> 1;
	}
}
/*
归并排序，找到最小有序子数组，再合并
*/
// 合并两个有序子数组 [left, mid] 和 [mid+1, right]
void merge(int arr[], int left, int mid, int right, int *tmp) {
	int i = left;    // 左子数组指针
	int j = mid + 1; // 右子数组指针
	int k = left;    // 临时数组指针

	// 合并左右子数组到临时数组（直到其中一个子数组遍历完毕）
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++]; // 左子数组元素更小，优先放入临时数组
		}
		else {
			tmp[k++] = arr[j++]; // 右子数组元素更小，优先放入临时数组
		}
	}

	// 处理左子数组的剩余元素（若有）
	while (i <= mid) {
		tmp[k++] = arr[i++];
	}

	// 处理右子数组的剩余元素（若有）
	while (j <= right) {
		tmp[k++] = arr[j++];
	}

	// 将临时数组的内容复制回原数组
	for (i = left; i <= right; i++) {
		arr[i] = tmp[i];
	}
}

// 分治递归函数：分割数组并合并
void divide_merge(int arr[], int left, int right, int *tmp) {
	if (left >= right) { // 递归终止条件：子数组长度为1或空
		return;
	}
	int mid = left + (right - left) / 2; // 计算中点（防止整数溢出）
	divide_merge(arr, left, mid, tmp);   // 递归排序左半部分
	divide_merge(arr, mid + 1, right, tmp); // 递归排序右半部分
	merge(arr, left, mid, right, tmp);   // 合并左右有序子数组
}

// 归并排序入口函数
void merge_sort(int arr[], int len) {
	int *tmp = (int *)calloc(len, sizeof(int)); // 分配临时数组（初始化为0）
	if (tmp == NULL) { // 检查内存分配是否成功
		printf("Memory allocation failed!\n");
		return;
	}
	divide_merge(arr, 0, len - 1, tmp); // 分治排序
	free(tmp); // 释放临时数组
	print_arr(arr, len); // 输出排序结果
}

/*
分区函数 应用在快排
*/
// 单向分区快速排序算法,有个特殊点
void quick_sort_one_way(int arr[], int low, int high) {
	if (low >= high) return;  // 递归终止条件

	// 选择基准值（这里选最后一个元素）
	int pivot = arr[high];
	int i = low - 1;  // 记录小于pivot的元素的右边界

	// 遍历数组，将小于pivot的元素移到左边
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			SWAP(arr, i, j);
		}
	}
	// 将pivot放到正确位置（i+1）
	SWAP(arr, i + 1, high);

	// 递归排序左右子数组
	quick_sort_one_way(arr, low, i);      // 左半部分（小于pivot）
	quick_sort_one_way(arr, i + 2, high); // 右半部分（大于pivot）
}

void quick_sort_two_way(int arr[], int low, int high) {
	if (low >= high) return;  // 递归终止条件

	// 选择基准值（这里选中间的元素，避免极端情况性能退化）
	int pivot = arr[(low + high) / 2];
	int left = low - 1;   // 左指针（初始在low左侧）
	int right = high + 1; // 右指针（初始在high右侧）

	while (1) {
		// 左指针右移，直到找到大于等于pivot的元素
		do {
			left++;
		} while (arr[left] < pivot);
		// 右指针左移，直到找到小于等于pivot的元素
		do {
			right--;
		} while (arr[right] > pivot);

		// 指针相遇或交叉，结束分区
		if (left >= right) break;

		// 交换左右指针的元素
		SWAP(arr, left, right);
	}

	// 递归排序左右子数组（right为分区点）
	quick_sort_two_way(arr, low, right);
	quick_sort_two_way(arr, right + 1, high);
}
/*
堆排序,堆化，该下标跟左右比，小，和最大的换位置
交换后，依旧跟左右比
*/
/*
堆排序
*/
void heapify(int arr[], int root_index, int tree_len) {
	while (1) {
		int left_chile_idx = 2 * root_index + 1;
		int right_chile_idx = 2 * root_index + 2;
		int max_index = (left_chile_idx<tree_len && arr[left_chile_idx]>arr[root_index]) ? left_chile_idx : root_index;
		max_index = (right_chile_idx<tree_len && arr[right_chile_idx]>arr[max_index]) ? right_chile_idx : max_index;
		if (max_index != root_index) {
			SWAP(arr, max_index, root_index);
			root_index = max_index;
		}
		else {
			break;
		}
	}
}
void heap_sort(int arr[], int len) {
	for (int i = len - 1; i >= 0; i--) {
		heapify(arr, i, len);
	}
	//此时已经是大根堆
	for (int i = len - 1; i >= 0; i--) {
		SWAP(arr, 0, i);
		heapify(arr, 0, i);
	}
}

int main(void) {
	int arr[] = { 1, 21, 45, 231, 99, 2, 18, 7, 4, 9 };
	int len = ARR_SIZE(arr);
	insertion_sort(arr, len);
	return 0;
}