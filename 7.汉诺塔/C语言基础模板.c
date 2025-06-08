#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 递归函数：将n个盘子从start塔移动到target塔，sup为辅助塔
void move(int n, char start, char sup, char target) {
    // 递归出口：仅1个盘子时，直接移动
    if (n == 1) {
        printf("%c --> %c\n", start, target);
        return;
    }

    // 第一步：将n-1个盘子从start移动到sup（target作为辅助）
    move(n - 1, start, target, sup);

    // 第二步：将最大的盘子从start移动到target（直接打印）
    printf("%c --> %c\n", start, target);

    // 第三步：将n-1个盘子从sup移动到target（start作为辅助）
    move(n - 1, sup, start, target);
}

int main() {
    int n = 3;
    long long steps = (1LL << n) - 1;  // 计算最少步数：2^n - 1
    printf("完成%d个盘子的汉诺塔问题，最少需要%lld步，全部移动轨迹如下：\n", n, steps);

    move(n, 'A', 'B', 'C');  // 调用递归函数输出移动步骤
    return 0;
}