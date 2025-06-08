#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// �ݹ麯������n�����Ӵ�start���ƶ���target����supΪ������
void move(int n, char start, char sup, char target) {
    // �ݹ���ڣ���1������ʱ��ֱ���ƶ�
    if (n == 1) {
        printf("%c --> %c\n", start, target);
        return;
    }

    // ��һ������n-1�����Ӵ�start�ƶ���sup��target��Ϊ������
    move(n - 1, start, target, sup);

    // �ڶ��������������Ӵ�start�ƶ���target��ֱ�Ӵ�ӡ��
    printf("%c --> %c\n", start, target);

    // ����������n-1�����Ӵ�sup�ƶ���target��start��Ϊ������
    move(n - 1, sup, start, target);
}

int main() {
    int n = 3;
    long long steps = (1LL << n) - 1;  // �������ٲ�����2^n - 1
    printf("���%d�����ӵĺ�ŵ�����⣬������Ҫ%lld����ȫ���ƶ��켣���£�\n", n, steps);

    move(n, 'A', 'B', 'C');  // ���õݹ麯������ƶ�����
    return 0;
}