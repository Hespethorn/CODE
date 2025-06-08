#include <stdio.h>
#include "function.h"

// ����ʵ�֣��ж������Ƿ�Ϊ���������λ�Ƿ�Ϊ1��
void is_odd(int num) {
    // �����Ķ��������λһ����1���� num & 1 �������λ
    int result = num & 1;
    printf("���� %d �Ƿ�Ϊ������%s\n", num, result ? "��" : "��");
}

// ����ʵ�֣��ж��Ƿ�Ϊ2���ݣ������ƽ���һ��1��
void is_Power_of_two(int num) {
    // 2���ݱ�����������
    if (num <= 0) {
        printf("���� %d ����2���ݣ���Ϊ��������\n", num);
        return;
    }
    // �� num ��2���ݣ��� num & (num - 1) ��Ϊ0����8=1000��8-1=0111����������Ϊ0��
    int result = (num & (num - 1)) == 0;
    printf("���� %d �Ƿ�Ϊ2���ݣ�%s\n", num, result ? "��" : "��");
}

// ����ʵ�֣����������Чλ��Last Set Bit��
void find_lsb(int num) {
    if (num == 0) {  // 0û����Чλ
        printf("����0û�������Чλ\n");
        return;
    }
    // ���ò������ԣ�num & (-num) �ᱣ�����λ��1������λ����
    int lsb_value = num & (-num);
    printf("���� %d �������Чλֵ�ǣ�%d\n", num, lsb_value);
}

// ����ʵ�֣���������������ֵ���������ʱ�����棩
void change(int *a, int *b) {
    if (a == b) return;  // ������ͬ��ַ����½��Ϊ0
    *a ^= *b;  // a = a ^ b
    *b ^= *a;  // b = (a ^ b) ^ b = a
    *a ^= *b;  // a = (a ^ b) ^ a = b
}

// ����ʵ�֣�����������Ψһ����һ�ε�Ԫ�أ�����������Σ�
int find_only(int nums[], int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result ^= nums[i];  // ������ʣ���ͬ�����Ϊ0��0����κ���Ϊ����
    }
    return result;
}

// ����ʵ�֣���������������Ψһ����һ�ε�Ԫ�أ�����������Σ�
void find_two(int nums[], int length) {
    if (length < 2) {
        printf("���鳤������Ϊ2\n");
        return;
    }

    // ��һ����򣺵õ�����ΨһԪ�ص����������Ϊ xor_sum��
    int xor_sum = 0;
    for (int i = 0; i < length; i++) {
        xor_sum ^= nums[i];
    }

    // �ҵ� xor_sum �����λ��1����λ������ΨһԪ�ز�ͬ��λ��
    int lsb = xor_sum & (-xor_sum);

    // �ڶ�����򣺰� lsb �������ÿ������Ϊһ��ΨһԪ��
    int a = 0, b = 0;
    for (int i = 0; i < length; i++) {
        if (nums[i] & lsb) {  // ��λΪ1��Ԫ�طֵ���a
            a ^= nums[i];
        }
        else {  // ��λΪ0��Ԫ�طֵ���b
            b ^= nums[i];
        }
    }
    printf("����������Ψһ���ֵ�Ԫ���ǣ�%d �� %d\n", a, b);
}