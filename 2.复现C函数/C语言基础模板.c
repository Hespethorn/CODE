#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>  // ����size_t����
#include"function.h"

// ���������������и��ֺ���
int main(void) {
    char p[30] = "122345";  // ���޸ĵ����飨��ʼ����6��
    char q[] = "12234";     // �Զ��Ƶ����ȣ�5+1=6��
    char a[] = "128757";    // �Զ��Ƶ����ȣ�6+1=7��

    // ���� my_strcmp���Ƚ�a��q��
    printf("my_strcmp(a, q) = %d\n", my_strcmp(a, q));  // ���������"128757" > "12234"��

    // ���� my_strlen������p�ĳ��ȣ�
    printf("my_strlen(p) = %zu\n", my_strlen(p));  // ���6���ַ�'1','2','2','3','4','5'��

    // ���� my_strcpy����q���Ƶ�p��
    printf("my_strcpy(p, q) = %s\n", my_strcpy(p, q));  // ���"12234"��p������Ϊq�����ݣ�

    // ���� my_strcmp���Ƚ��޸ĺ��p��q��
    printf("my_strcmp(p, q) = %d\n", my_strcmp(p, q));  // ���0������������ͬ��

    // ���� my_strncpy����a��ǰ4���ַ����Ƶ�p��
    printf("my_strncpy(p, a, 4) = %s\n", my_strncpy(p, a, 4));  // ���"1287"��pǰ4λ�����ǣ�

    // ���� my_strcat����aƴ����pĩβ��
    printf("my_strcat(p, a) = %s\n", my_strcat(p, a));  // ���"1287128757"��pĩβ׷��a�����ݣ�

    // ���� my_strncat����a��ǰ4���ַ�ƴ����pĩβ��
    printf("my_strncat(p, a, 4) = %s\n", my_strncat(p, a, 4));  // ���"128712871287"��pĩβ׷��ǰ4���ַ���

    // ���� my_strcpy���ٴν�q���Ƶ�p��
    printf("my_strcpy(p, q) = %s\n", my_strcpy(p, q));  // ���"12234"��p������Ϊq�����ݣ�

    return 0;
}