#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

/*
* 核心目标：对比二维数组（(*p)[]）与指针数组（*p[]）的类型差异与操作限制
* 关键结论：
*   - []优先级高于*，因此*p[]是数组的指针（指针数组），(*p)[]是数组的数组（二维数组）
*   - 二维数组名是常量指针（不可重新赋值），但可通过下标修改元素内容（需内存可写）
*   - 指针数组的元素是指针变量（可重新赋值指向新内存），但指向的内容是否可写取决于目标内存
*/

// 二维数组（数组的数组）：连续内存存储，每个子数组固定大小
char fruits1[][10] = { "apple", "banana", "cherry" };  // 3个元素，每个元素是char[10]

// 指针数组（数组的指针）：存储指针的数组，指针指向独立内存
char *fruits2[] = { "apple", "banana", "cherry" };      // 3个元素，每个元素是char*

// 指针数组指向栈上的字符数组（可写内存）
char apple_stack[] = "apple";   // 栈上的字符数组（可写）
char banana_stack[] = "banana"; // 栈上的字符数组（可写）
char cherry_stack[] = "cherry"; // 栈上的字符数组（可写）
char *fruits3[] = { apple_stack, banana_stack, cherry_stack }; // 指针数组指向栈数组

// 函数1：打印数组内容与长度（验证内存布局与可访问性）
void print_arrays() {
    printf("===== 打印二维数组 fruits1 =====\n");
    for (int i = 0; i < sizeof(fruits1) / sizeof(fruits1[0]); i++) {
        printf("fruits1[%d]: %s（长度：%zu，内存地址：%p）\n",
            i, fruits1[i], strlen(fruits1[i]), (void *)fruits1[i]);
    }

    printf("\n===== 打印指针数组 fruits2 =====\n");
    for (int i = 0; i < sizeof(fruits2) / sizeof(fruits2[0]); i++) {
        printf("fruits2[%d]: %s（长度：%zu，指针地址：%p，指向内存：%p）\n",
            i, fruits2[i], strlen(fruits2[i]), (void *)&fruits2[i], (void *)fruits2[i]);
    }

    printf("\n===== 打印指针数组 fruits3（指向栈数组） =====\n");
    for (int i = 0; i < sizeof(fruits3) / sizeof(fruits3[0]); i++) {
        printf("fruits3[%d]: %s（长度：%zu，指针地址：%p，指向内存：%p）\n",
            i, fruits3[i], strlen(fruits3[i]), (void *)&fruits3[i], (void *)fruits3[i]);
    }
}

// 函数2：修改数组元素（验证操作限制）
void modify_arrays() {
    // 1. 尝试修改二维数组的"数组名"（非法操作）
    // fruits1 = fruits2;  // 编译错误：数组名是常量指针，不可重新赋值

    // 2. 修改二维数组的内容（通过下标，合法）
    strcpy(fruits1[0], "orange");  // 正确：覆盖二维数组的内存内容
    fruits1[1][0] = 'B';           // 正确：修改二维数组的字符（原"banana"→"Banana"）

    // 3. 修改指针数组的"数组名"（非法操作）
    // fruits2 = fruits3;  // 错误：数组名是常量指针，不可重新赋值
    // 修正：指针数组的元素是指针，应逐个修改元素指向
    fruits2[0] = "orange";  // 正确：修改指针数组的第0个元素指向新字符串
    fruits2[1] = "Banana";  // 正确：修改指针数组的第1个元素指向新字符串（原"banana"未被修改）

    // 4. 修改指针数组指向的内容（取决于目标内存是否可写）
    fruits3[1][0] = 'b';  // 正确：修改栈上的banana_stack数组（可写内存）
    // fruits2[1][0] = 'b';  // 未定义行为！fruits2[1]指向字符串字面量（只读内存）
}

// 函数3：验证指针数组与二维数组的本质区别
void validate_differences() {
    // 二维数组的内存是连续的（所有字符在一个块中）
    printf("\n===== 验证二维数组内存连续性 =====\n");
    printf("fruits1[0]地址：%p，fruits1[0][0]地址：%p（偏移0）\n",
        (void *)fruits1, (void *)&fruits1[0][0]);
    printf("fruits1[0]地址：%p，fruits1[0][9]地址：%p（偏移9）\n",
        (void *)fruits1, (void *)&fruits1[0][9]);
    printf("fruits1[1]地址：%p（偏移10，与fruits1[0][9]+1一致）\n",
        (void *)fruits1[1]);

    // 指针数组的内存是非连续的（存储指针，指针指向分散内存）
    printf("\n===== 验证指针数组内存非连续性 =====\n");
    printf("fruits2[0]指针值：%p（指向字符串字面量）\n", (void *)fruits2[0]);
    printf("fruits2[1]指针值：%p（指向字符串字面量）\n", (void *)fruits2[1]);
    printf("fruits2[2]指针值：%p（指向字符串字面量）\n", (void *)fruits2[2]);
    printf("fruits2数组本身的地址：%p，与指针值无关\n", (void *)fruits2);
}

int main(void) {
    // 初始化后直接打印
    print_arrays();

    // 修改数组元素并再次打印
    modify_arrays();
    printf("\n===== 修改后的数组状态 =====\n");
    print_arrays();

    // 验证内存布局差异
    validate_differences();

    return 0;
}