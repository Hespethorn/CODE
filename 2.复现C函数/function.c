#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>  // 用于size_t类型
#include"function.h"

// 1. 实现 strlen 求字符的长度
size_t my_strlen(const char *p) {
    size_t count = 0;
    while (*p != '\0') {  // 遍历直到空终止符
        count++;
        p++;              // 移动到下一个字符
    }
    return count;
}

// 2. 实现 strcpy 复制字符串的值
char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;       // 保存目标起始地址
    while (*src != '\0') {  // 复制直到源字符串结束
        *dest++ = *src++;   // 逐个字符复制（后置++避免覆盖）
    }
    *dest = '\0';           // 手动添加空终止符
    return tmp;             // 返回目标起始地址
}

// 3. 更安全的复制（带长度限制）
char *my_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        // 复制前n个有效字符
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        // 填充剩余空间为\0
        dest[i] = '\0';
    }
    return dest;
}

// 4. 实现 strcat 拼接字符串
char *my_strcat(char *dest, const char *src) {
    char *tmp = dest;
    // 保存目标起始地址
    while (*dest != '\0') {
        // 找到dest的末尾（空终止符位置）
        dest++;
    }
    while ((*dest++ = *src++) != '\0');
    // 复制src到dest末尾
    *dest = '\0';
    // 手动添加空终止符（防止src未终止导致dest越界）
    return tmp;
    // 返回目标起始地址
}

// 5. 实现 strncat 安全拼接（限制长度）
char *my_strncat(char *dest, const char *src, size_t n) {
    char *tmp = dest;       // 保存目标起始地址
    while (*dest != '\0') { // 找到dest的末尾
        dest++;
    }
    for (size_t i = 0; i < n && *src != '\0'; i++) {  // 复制前n个字符（或源提前结束）
        *dest++ = *src++;
    }
    *dest = '\0';           // 手动添加空终止符
    return tmp;             // 返回目标起始地址
}

// 6. 实现 strcmp 比较字符串大小
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {  // 字符相同且未结束则继续
        str1++;
        str2++;
    }
    // 返回差值（转换为unsigned char避免符号扩展问题）
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}