#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>  // 用于size_t类型
#include"function.h"

// 主函数：测试所有复现函数
int main(void) {
    char p[30] = "122345";  // 可修改的数组（初始长度6）
    char q[] = "12234";     // 自动推导长度（5+1=6）
    char a[] = "128757";    // 自动推导长度（6+1=7）

    // 测试 my_strcmp（比较a和q）
    printf("my_strcmp(a, q) = %d\n", my_strcmp(a, q));  // 输出正数（"128757" > "12234"）

    // 测试 my_strlen（计算p的长度）
    printf("my_strlen(p) = %zu\n", my_strlen(p));  // 输出6（字符'1','2','2','3','4','5'）

    // 测试 my_strcpy（将q复制到p）
    printf("my_strcpy(p, q) = %s\n", my_strcpy(p, q));  // 输出"12234"（p被覆盖为q的内容）

    // 测试 my_strcmp（比较修改后的p和q）
    printf("my_strcmp(p, q) = %d\n", my_strcmp(p, q));  // 输出0（两者内容相同）

    // 测试 my_strncpy（将a的前4个字符复制到p）
    printf("my_strncpy(p, a, 4) = %s\n", my_strncpy(p, a, 4));  // 输出"1287"（p前4位被覆盖）

    // 测试 my_strcat（将a拼接至p末尾）
    printf("my_strcat(p, a) = %s\n", my_strcat(p, a));  // 输出"1287128757"（p末尾追加a的内容）

    // 测试 my_strncat（将a的前4个字符拼接至p末尾）
    printf("my_strncat(p, a, 4) = %s\n", my_strncat(p, a, 4));  // 输出"128712871287"（p末尾追加前4个字符）

    // 测试 my_strcpy（再次将q复制到p）
    printf("my_strcpy(p, q) = %s\n", my_strcpy(p, q));  // 输出"12234"（p被覆盖为q的内容）

    return 0;
}