#ifndef FUNCTION_H  // 防止头文件重复包含
#define FUNCTION_H

// 函数声明：判断整数是否为奇数
void is_odd(int num);

// 函数声明：判断是否为2的幂
void is_Power_of_two(int num);

// 函数声明：查找最低有效位（Last Set Bit）
void find_lsb(int num);

// 函数声明：交换两个整数的值（异或实现）
void change(int *a, int *b);  // 注意：必须用指针传递才能修改原变量

// 函数声明：查找数组中唯一出现一次的元素（其余出现两次）
int find_only(int nums[], int length);

// 函数声明：查找数组中两个唯一出现一次的元素（其余出现两次）
void find_two(int nums[], int length);

#endif