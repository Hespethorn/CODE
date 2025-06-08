#include <stdio.h>
#include "function.h"

// 函数实现：判断整数是否为奇数（最低位是否为1）
void is_odd(int num) {
    // 奇数的二进制最低位一定是1，用 num & 1 保留最低位
    int result = num & 1;
    printf("数字 %d 是否为奇数？%s\n", num, result ? "是" : "否");
}

// 函数实现：判断是否为2的幂（二进制仅有一个1）
void is_Power_of_two(int num) {
    // 2的幂必须是正整数
    if (num <= 0) {
        printf("数字 %d 不是2的幂（需为正整数）\n", num);
        return;
    }
    // 若 num 是2的幂，则 num & (num - 1) 必为0（如8=1000，8-1=0111，与运算结果为0）
    int result = (num & (num - 1)) == 0;
    printf("数字 %d 是否为2的幂？%s\n", num, result ? "是" : "否");
}

// 函数实现：查找最低有效位（Last Set Bit）
void find_lsb(int num) {
    if (num == 0) {  // 0没有有效位
        printf("数字0没有最低有效位\n");
        return;
    }
    // 利用补码特性：num & (-num) 会保留最低位的1，其余位清零
    int lsb_value = num & (-num);
    printf("数字 %d 的最低有效位值是：%d\n", num, lsb_value);
}

// 函数实现：交换两个整数的值（异或无临时变量版）
void change(int *a, int *b) {
    if (a == b) return;  // 避免相同地址异或导致结果为0
    *a ^= *b;  // a = a ^ b
    *b ^= *a;  // b = (a ^ b) ^ b = a
    *a ^= *b;  // a = (a ^ b) ^ a = b
}

// 函数实现：查找数组中唯一出现一次的元素（其余出现两次）
int find_only(int nums[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result ^= nums[i];  // 异或性质：相同数异或为0，0异或任何数为自身
    }
    return result;
}

// 函数实现：查找数组中两个唯一出现一次的元素（其余出现两次）
void find_two(int nums[], int length) {
    if (length < 2) {
        printf("数组长度至少为2\n");
        return;
    }

    // 第一轮异或：得到两个唯一元素的异或结果（记为 xor_sum）
    int xor_sum = 0;
    for (int i = 0; i < length; i++) {
        xor_sum ^= nums[i];
    }

    // 找到 xor_sum 中最低位的1（该位是两个唯一元素不同的位）
    int lsb = xor_sum & (-xor_sum);

    // 第二轮异或：按 lsb 分组异或，每组结果即为一个唯一元素
    int a = 0, b = 0;
    for (int i = 0; i < length; i++) {
        if (nums[i] & lsb) {  // 该位为1的元素分到组a
            a ^= nums[i];
        }
        else {  // 该位为0的元素分到组b
            b ^= nums[i];
        }
    }
    printf("数组中两个唯一出现的元素是：%d 和 %d\n", a, b);
}