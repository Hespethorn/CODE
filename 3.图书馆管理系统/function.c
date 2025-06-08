#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "function.h"

const char *Genre_Zn(Genre i) {
	switch (i) {
	case SCIENCE_FICTION: return "�ƻ�";
	case LITERATURE:         return "��ѧ";
	case HISTORY:          return "��ʷ";
	case TECHNOLOGY:          return "�Ƽ�";
	case OTHER:          return "����";
	default:              return "δ֪";
	}
}

void print_book_info(Book *books, int count) {
	for (int i = 0; i < 21; i++) printf("-");
	printf(" ���е��鼮��Ϣ ");
	for (int i = 0; i < 21; i++) printf("-");
	printf("\n");

	for (int i = 0; i < MAX_BOOKS; i++) {
		printf("���:%-2d  ����:%-12s  ����:%-13s   ���:%-8s\n", books[i].num, books[i].name, books[i].author, Genre_Zn(books[i].genre));
	}
}

void find_books_by_genre(Book *books, int count, Genre genre) {
	for (int i = 0; i < count; i++) {
		if (books[i].genre == genre) {
			printf("���:%-2d  ����:%-12s  ����:%-13s   ���:%-8s\n", books[i].num, books[i].name, books[i].author, Genre_Zn(books[i].genre));
		}
	}
}