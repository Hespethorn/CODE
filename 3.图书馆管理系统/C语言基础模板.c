#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "function.h"

Book books[MAX_BOOKS] = {
    {1, "����", "������", SCIENCE_FICTION},
    {2, "��¥��", "��ѩ��", LITERATURE},
    {3, "�й�ͨʷ", "��˼��", HISTORY},
    {4, "ʱ���ʷ", "ʷ�ٷ�_����", TECHNOLOGY},
    {5, "Χ��", "Ǯ����", LITERATURE},
    {6, "������ƫ��", "��_��˹͡", LITERATURE},
    {7, "��Хɽׯ", "������_������", LITERATURE},
    {8, "����", "�໪", LITERATURE},
    {9, "������Щ�¶�", "��������", HISTORY},
    {10, "�ں�֮��", "��˹����_����", OTHER}
};

int main(void) {
    print_book_info(books, MAX_BOOKS);
    Genre gen;
    do {
        printf("\n�������鼮����ţ�0:�ƻ� 1.��ѧ 2.��ʷ 3.�Ƽ� 4.���� 5.�˳���\n");
            scanf("%d", &gen);
        find_books_by_genre(books, MAX_BOOKS, gen);
    } while (gen != 5);
    return 0;
}