#define _CRT_SECURE_NO_WARNINGS  // 关闭VS编译器的安全警告（如scanf）
#include <stdio.h>
#include "function.h"  // 包含函数声明

int main(void) {
    int num = 0;
    printf("请输入你要查询的整数：\n");
        scanf(" %d", &num);
    // 输入整数（注意空格跳过换行符）

    // 测试单个数字的位运算功能
    is_odd(num);          // 判断奇偶
    is_Power_of_two(num); // 判断是否为2的幂
    find_lsb(num);        // 查找最低有效位

    // 测试数组的唯一元素查找功能（示例数组）
    int test_array[] = { 2, 3, 2, 4, 5, 5, 3, 6 };
    // 示例数组：2、4、6各出现一次，其余出现两次
    int array_length = sizeof(test_array) / sizeof(test_array[0]);
    // 计算数组长度

    printf("--- 数组唯一元素测试 ---\n");
    find_two(test_array, array_length);
    // 查找两个唯一元素（本例中是4和6）

    // 测试交换函数（可选）
    int a = 10, b = 20;
    printf("交换前：a=%d, b=%d\n", a, b);
    change(&a, &b);  // 传递指针以修改原变量
    printf("交换后：a=%d, b=%d\n", a, b);
    return 0;
}