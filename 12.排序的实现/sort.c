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

/*
ϣ�������ص�һ�ζ�������𽥼�С�����
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
�鲢�����ҵ���С���������飬�ٺϲ�
*/
// �ϲ��������������� [left, mid] �� [mid+1, right]
void merge(int arr[], int left, int mid, int right, int *tmp) {
	int i = left;    // ��������ָ��
	int j = mid + 1; // ��������ָ��
	int k = left;    // ��ʱ����ָ��

	// �ϲ����������鵽��ʱ���飨ֱ������һ�������������ϣ�
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			tmp[k++] = arr[i++]; // ��������Ԫ�ظ�С�����ȷ�����ʱ����
		}
		else {
			tmp[k++] = arr[j++]; // ��������Ԫ�ظ�С�����ȷ�����ʱ����
		}
	}

	// �������������ʣ��Ԫ�أ����У�
	while (i <= mid) {
		tmp[k++] = arr[i++];
	}

	// �������������ʣ��Ԫ�أ����У�
	while (j <= right) {
		tmp[k++] = arr[j++];
	}

	// ����ʱ��������ݸ��ƻ�ԭ����
	for (i = left; i <= right; i++) {
		arr[i] = tmp[i];
	}
}

// ���εݹ麯�����ָ����鲢�ϲ�
void divide_merge(int arr[], int left, int right, int *tmp) {
	if (left >= right) { // �ݹ���ֹ�����������鳤��Ϊ1���
		return;
	}
	int mid = left + (right - left) / 2; // �����е㣨��ֹ���������
	divide_merge(arr, left, mid, tmp);   // �ݹ�������벿��
	divide_merge(arr, mid + 1, right, tmp); // �ݹ������Ұ벿��
	merge(arr, left, mid, right, tmp);   // �ϲ���������������
}

// �鲢������ں���
void merge_sort(int arr[], int len) {
	int *tmp = (int *)calloc(len, sizeof(int)); // ������ʱ���飨��ʼ��Ϊ0��
	if (tmp == NULL) { // ����ڴ�����Ƿ�ɹ�
		printf("Memory allocation failed!\n");
		return;
	}
	divide_merge(arr, 0, len - 1, tmp); // ��������
	free(tmp); // �ͷ���ʱ����
	print_arr(arr, len); // ���������
}

/*
�������� Ӧ���ڿ���
*/
// ����������������㷨,�и������
void quick_sort_one_way(int arr[], int low, int high) {
	if (low >= high) return;  // �ݹ���ֹ����

	// ѡ���׼ֵ������ѡ���һ��Ԫ�أ�
	int pivot = arr[high];
	int i = low - 1;  // ��¼С��pivot��Ԫ�ص��ұ߽�

	// �������飬��С��pivot��Ԫ���Ƶ����
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			SWAP(arr, i, j);
		}
	}
	// ��pivot�ŵ���ȷλ�ã�i+1��
	SWAP(arr, i + 1, high);

	// �ݹ���������������
	quick_sort_one_way(arr, low, i);      // ��벿�֣�С��pivot��
	quick_sort_one_way(arr, i + 2, high); // �Ұ벿�֣�����pivot��
}

void quick_sort_two_way(int arr[], int low, int high) {
	if (low >= high) return;  // �ݹ���ֹ����

	// ѡ���׼ֵ������ѡ�м��Ԫ�أ����⼫����������˻���
	int pivot = arr[(low + high) / 2];
	int left = low - 1;   // ��ָ�루��ʼ��low��ࣩ
	int right = high + 1; // ��ָ�루��ʼ��high�Ҳࣩ

	while (1) {
		// ��ָ�����ƣ�ֱ���ҵ����ڵ���pivot��Ԫ��
		do {
			left++;
		} while (arr[left] < pivot);
		// ��ָ�����ƣ�ֱ���ҵ�С�ڵ���pivot��Ԫ��
		do {
			right--;
		} while (arr[right] > pivot);

		// ָ�������򽻲棬��������
		if (left >= right) break;

		// ��������ָ���Ԫ��
		SWAP(arr, left, right);
	}

	// �ݹ��������������飨rightΪ�����㣩
	quick_sort_two_way(arr, low, right);
	quick_sort_two_way(arr, right + 1, high);
}
/*
������,�ѻ������±�����ұȣ�С�������Ļ�λ��
���������ɸ����ұ�
*/
/*
������
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
	//��ʱ�Ѿ��Ǵ����
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