#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>  // ����size_t����
#include"function.h"

// 1. ʵ�� strlen ���ַ��ĳ���
size_t my_strlen(const char *p) {
    size_t count = 0;
    while (*p != '\0') {  // ����ֱ������ֹ��
        count++;
        p++;              // �ƶ�����һ���ַ�
    }
    return count;
}

// 2. ʵ�� strcpy �����ַ�����ֵ
char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;       // ����Ŀ����ʼ��ַ
    while (*src != '\0') {  // ����ֱ��Դ�ַ�������
        *dest++ = *src++;   // ����ַ����ƣ�����++���⸲�ǣ�
    }
    *dest = '\0';           // �ֶ���ӿ���ֹ��
    return tmp;             // ����Ŀ����ʼ��ַ
}

// 3. ����ȫ�ĸ��ƣ����������ƣ�
char *my_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        // ����ǰn����Ч�ַ�
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        // ���ʣ��ռ�Ϊ\0
        dest[i] = '\0';
    }
    return dest;
}

// 4. ʵ�� strcat ƴ���ַ���
char *my_strcat(char *dest, const char *src) {
    char *tmp = dest;
    // ����Ŀ����ʼ��ַ
    while (*dest != '\0') {
        // �ҵ�dest��ĩβ������ֹ��λ�ã�
        dest++;
    }
    while ((*dest++ = *src++) != '\0');
    // ����src��destĩβ
    *dest = '\0';
    // �ֶ���ӿ���ֹ������ֹsrcδ��ֹ����destԽ�磩
    return tmp;
    // ����Ŀ����ʼ��ַ
}

// 5. ʵ�� strncat ��ȫƴ�ӣ����Ƴ��ȣ�
char *my_strncat(char *dest, const char *src, size_t n) {
    char *tmp = dest;       // ����Ŀ����ʼ��ַ
    while (*dest != '\0') { // �ҵ�dest��ĩβ
        dest++;
    }
    for (size_t i = 0; i < n && *src != '\0'; i++) {  // ����ǰn���ַ�����Դ��ǰ������
        *dest++ = *src++;
    }
    *dest = '\0';           // �ֶ���ӿ���ֹ��
    return tmp;             // ����Ŀ����ʼ��ַ
}

// 6. ʵ�� strcmp �Ƚ��ַ�����С
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {  // �ַ���ͬ��δ���������
        str1++;
        str2++;
    }
    // ���ز�ֵ��ת��Ϊunsigned char���������չ���⣩
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}