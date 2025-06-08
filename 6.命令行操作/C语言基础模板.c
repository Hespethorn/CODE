#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
命令行操作，main函数传参，调试，看输出情况
*/
int main(int argc, char *argv[]) {
    // 检查参数数量是否足够（至少4个参数：程序名、整数、浮点数、结果描述）
    if (argc < 4) {
        printf("错误：需要至少4个参数（格式：程序名 整数 浮点数 结果描述）\n");
        return 1;
    }

    int num1;
    double num2;

    // 解析整数参数（argv[1]）
    int ret1 = sscanf(argv[1], "%d", &num1);
    if (ret1 != 1) {
        printf("错误：第一个参数必须是整数（当前值：%s）\n", argv[1]);
        return 1;
    }

    // 解析浮点数参数（argv[2]）
    int ret2 = sscanf(argv[2], "%lf", &num2);
    if (ret2 != 1) {
        printf("错误：第二个参数必须是浮点数（当前值：%s）\n", argv[2]);
        return 1;
    }

    // 计算和
    double num3 = num1 + num2;

    // 格式化输出结果（使用argv[3]作为描述）
    printf("结果字符串：%d + %.2lf = %.2lf %s\n", num1, num2, num3, argv[3]);

    return 0;
}