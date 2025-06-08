#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "function.h"

const char *Genre_Zn(Genre i) {
	switch (i) {
	case SCIENCE_FICTION: return "科幻";
	case LITERATURE:         return "文学";
	case HISTORY:          return "历史";
	case TECHNOLOGY:          return "科技";
	case OTHER:          return "其他";
	default:              return "未知";
	}
}

void print_book_info(Book *books, int count) {
	for (int i = 0; i < 21; i++) printf("-");
	printf(" 所有的书籍信息 ");
	for (int i = 0; i < 21; i++) printf("-");
	printf("\n");

	for (int i = 0; i < MAX_BOOKS; i++) {
		printf("编号:%-2d  书名:%-12s  作者:%-13s   类别:%-8s\n", books[i].num, books[i].name, books[i].author, Genre_Zn(books[i].genre));
	}
}

void find_books_by_genre(Book *books, int count, Genre genre) {
	for (int i = 0; i < count; i++) {
		if (books[i].genre == genre) {
			printf("编号:%-2d  书名:%-12s  作者:%-13s   类别:%-8s\n", books[i].num, books[i].name, books[i].author, Genre_Zn(books[i].genre));
		}
	}
}