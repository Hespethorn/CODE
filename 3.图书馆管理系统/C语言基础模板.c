#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "function.h"

Book books[MAX_BOOKS] = {
    {1, "三体", "刘慈欣", SCIENCE_FICTION},
    {2, "红楼梦", "曹雪芹", LITERATURE},
    {3, "中国通史", "吕思勉", HISTORY},
    {4, "时间简史", "史蒂芬_霍金", TECHNOLOGY},
    {5, "围城", "钱钟书", LITERATURE},
    {6, "傲慢与偏见", "简_奥斯汀", LITERATURE},
    {7, "呼啸山庄", "艾米莉_勃朗特", LITERATURE},
    {8, "活着", "余华", LITERATURE},
    {9, "明朝那些事儿", "当年明月", HISTORY},
    {10, "乌合之众", "古斯塔夫_勒庞", OTHER}
};

int main(void) {
    print_book_info(books, MAX_BOOKS);
    Genre gen;
    do {
        printf("\n请输入书籍类别编号（0:科幻 1.文学 2.历史 3.科技 4.其他 5.退出）\n");
            scanf("%d", &gen);
        find_books_by_genre(books, MAX_BOOKS, gen);
    } while (gen != 5);
    return 0;
}