#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
* ����Ŀ�꣺�Աȶ�ά���飨(*p)[]����ָ�����飨*p[]�������Ͳ������������
* �ؼ����ۣ�
*   - []���ȼ�����*�����*p[]�������ָ�루ָ�����飩��(*p)[]����������飨��ά���飩
*   - ��ά�������ǳ���ָ�루�������¸�ֵ��������ͨ���±��޸�Ԫ�����ݣ����ڴ��д��
*   - ָ�������Ԫ����ָ������������¸�ֵָ�����ڴ棩����ָ��������Ƿ��дȡ����Ŀ���ڴ�
*/

// ��ά���飨��������飩�������ڴ�洢��ÿ��������̶���С
char fruits1[][10] = { "apple", "banana", "cherry" };  // 3��Ԫ�أ�ÿ��Ԫ����char[10]

// ָ�����飨�����ָ�룩���洢ָ������飬ָ��ָ������ڴ�
char *fruits2[] = { "apple", "banana", "cherry" };      // 3��Ԫ�أ�ÿ��Ԫ����char*

// ָ������ָ��ջ�ϵ��ַ����飨��д�ڴ棩
char apple_stack[] = "apple";   // ջ�ϵ��ַ����飨��д��
char banana_stack[] = "banana"; // ջ�ϵ��ַ����飨��д��
char cherry_stack[] = "cherry"; // ջ�ϵ��ַ����飨��д��
char *fruits3[] = { apple_stack, banana_stack, cherry_stack }; // ָ������ָ��ջ����

// ����1����ӡ���������볤�ȣ���֤�ڴ沼����ɷ����ԣ�
void print_arrays() {
    printf("===== ��ӡ��ά���� fruits1 =====\n");
    for (int i = 0; i < sizeof(fruits1) / sizeof(fruits1[0]); i++) {
        printf("fruits1[%d]: %s�����ȣ�%zu���ڴ��ַ��%p��\n",
            i, fruits1[i], strlen(fruits1[i]), (void *)fruits1[i]);
    }

    printf("\n===== ��ӡָ������ fruits2 =====\n");
    for (int i = 0; i < sizeof(fruits2) / sizeof(fruits2[0]); i++) {
        printf("fruits2[%d]: %s�����ȣ�%zu��ָ���ַ��%p��ָ���ڴ棺%p��\n",
            i, fruits2[i], strlen(fruits2[i]), (void *)&fruits2[i], (void *)fruits2[i]);
    }

    printf("\n===== ��ӡָ������ fruits3��ָ��ջ���飩 =====\n");
    for (int i = 0; i < sizeof(fruits3) / sizeof(fruits3[0]); i++) {
        printf("fruits3[%d]: %s�����ȣ�%zu��ָ���ַ��%p��ָ���ڴ棺%p��\n",
            i, fruits3[i], strlen(fruits3[i]), (void *)&fruits3[i], (void *)fruits3[i]);
    }
}

// ����2���޸�����Ԫ�أ���֤�������ƣ�
void modify_arrays() {
    // 1. �����޸Ķ�ά�����"������"���Ƿ�������
    // fruits1 = fruits2;  // ��������������ǳ���ָ�룬�������¸�ֵ

    // 2. �޸Ķ�ά��������ݣ�ͨ���±꣬�Ϸ���
    strcpy(fruits1[0], "orange");  // ��ȷ�����Ƕ�ά������ڴ�����
    fruits1[1][0] = 'B';           // ��ȷ���޸Ķ�ά������ַ���ԭ"banana"��"Banana"��

    // 3. �޸�ָ�������"������"���Ƿ�������
    // fruits2 = fruits3;  // �����������ǳ���ָ�룬�������¸�ֵ
    // ������ָ�������Ԫ����ָ�룬Ӧ����޸�Ԫ��ָ��
    fruits2[0] = "orange";  // ��ȷ���޸�ָ������ĵ�0��Ԫ��ָ�����ַ���
    fruits2[1] = "Banana";  // ��ȷ���޸�ָ������ĵ�1��Ԫ��ָ�����ַ�����ԭ"banana"δ���޸ģ�

    // 4. �޸�ָ������ָ������ݣ�ȡ����Ŀ���ڴ��Ƿ��д��
    fruits3[1][0] = 'b';  // ��ȷ���޸�ջ�ϵ�banana_stack���飨��д�ڴ棩
    // fruits2[1][0] = 'b';  // δ������Ϊ��fruits2[1]ָ���ַ�����������ֻ���ڴ棩
}

// ����3����ָ֤���������ά����ı�������
void validate_differences() {
    // ��ά������ڴ��������ģ������ַ���һ�����У�
    printf("\n===== ��֤��ά�����ڴ������� =====\n");
    printf("fruits1[0]��ַ��%p��fruits1[0][0]��ַ��%p��ƫ��0��\n",
        (void *)fruits1, (void *)&fruits1[0][0]);
    printf("fruits1[0]��ַ��%p��fruits1[0][9]��ַ��%p��ƫ��9��\n",
        (void *)fruits1, (void *)&fruits1[0][9]);
    printf("fruits1[1]��ַ��%p��ƫ��10����fruits1[0][9]+1һ�£�\n",
        (void *)fruits1[1]);

    // ָ��������ڴ��Ƿ������ģ��洢ָ�룬ָ��ָ���ɢ�ڴ棩
    printf("\n===== ��ָ֤�������ڴ�������� =====\n");
    printf("fruits2[0]ָ��ֵ��%p��ָ���ַ�����������\n", (void *)fruits2[0]);
    printf("fruits2[1]ָ��ֵ��%p��ָ���ַ�����������\n", (void *)fruits2[1]);
    printf("fruits2[2]ָ��ֵ��%p��ָ���ַ�����������\n", (void *)fruits2[2]);
    printf("fruits2���鱾��ĵ�ַ��%p����ָ��ֵ�޹�\n", (void *)fruits2);
}

int main(void) {
    // ��ʼ����ֱ�Ӵ�ӡ
    print_arrays();

    // �޸�����Ԫ�ز��ٴδ�ӡ
    modify_arrays();
    printf("\n===== �޸ĺ������״̬ =====\n");
    print_arrays();

    // ��֤�ڴ沼�ֲ���
    validate_differences();

    return 0;
}