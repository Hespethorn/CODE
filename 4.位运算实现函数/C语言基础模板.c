#define _CRT_SECURE_NO_WARNINGS  // �ر�VS�������İ�ȫ���棨��scanf��
#include <stdio.h>
#include "function.h"  // ������������

int main(void) {
    int num = 0;
    printf("��������Ҫ��ѯ��������\n");
        scanf(" %d", &num);
    // ����������ע��ո��������з���

    // ���Ե������ֵ�λ���㹦��
    is_odd(num);          // �ж���ż
    is_Power_of_two(num); // �ж��Ƿ�Ϊ2����
    find_lsb(num);        // ���������Чλ

    // ���������ΨһԪ�ز��ҹ��ܣ�ʾ�����飩
    int test_array[] = { 2, 3, 2, 4, 5, 5, 3, 6 };
    // ʾ�����飺2��4��6������һ�Σ������������
    int array_length = sizeof(test_array) / sizeof(test_array[0]);
    // �������鳤��

    printf("--- ����ΨһԪ�ز��� ---\n");
    find_two(test_array, array_length);
    // ��������ΨһԪ�أ���������4��6��

    // ���Խ�����������ѡ��
    int a = 10, b = 20;
    printf("����ǰ��a=%d, b=%d\n", a, b);
    change(&a, &b);  // ����ָ�����޸�ԭ����
    printf("������a=%d, b=%d\n", a, b);
    return 0;
}