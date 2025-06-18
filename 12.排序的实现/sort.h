#ifndef SORT_H
#define SORT_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SWAP(arr, i, j ) {      \
    int tmp = arr[i];           \
    arr[i] = arr[j];            \
    arr[j] = tmp;               \
}
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))











#endif // !SORT_H


