#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
�����в�����main�������Σ����ԣ���������
*/
int main(int argc, char *argv[]) {
    // �����������Ƿ��㹻������4���������������������������������������
    if (argc < 4) {
        printf("������Ҫ����4����������ʽ�������� ���� ������ ���������\n");
        return 1;
    }

    int num1;
    double num2;

    // ��������������argv[1]��
    int ret1 = sscanf(argv[1], "%d", &num1);
    if (ret1 != 1) {
        printf("���󣺵�һ��������������������ǰֵ��%s��\n", argv[1]);
        return 1;
    }

    // ����������������argv[2]��
    int ret2 = sscanf(argv[2], "%lf", &num2);
    if (ret2 != 1) {
        printf("���󣺵ڶ������������Ǹ���������ǰֵ��%s��\n", argv[2]);
        return 1;
    }

    // �����
    double num3 = num1 + num2;

    // ��ʽ����������ʹ��argv[3]��Ϊ������
    printf("����ַ�����%d + %.2lf = %.2lf %s\n", num1, num2, num3, argv[3]);

    return 0;
}