#ifndef FUNCTION_H
#define FUNCTION_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX_BOOKS 10

typedef enum Genre {
    SCIENCE_FICTION = 0,
    LITERATURE = 1,
    HISTORY = 2,
    TECHNOLOGY = 3,
    OTHER = 4
} Genre;

typedef struct Book {
    int num;
    char name[15];
    char author[20];
    Genre genre;
} Book;

const char *Genre_Zn(Genre i);
void print_book_info(Book *books, int count);
void find_books_by_genre(Book *books, int count, Genre genre);
#endif