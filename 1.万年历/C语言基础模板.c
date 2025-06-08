#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdbool.h>
#include"function.h"

int main(void) {
	
	do {
		printf("请输入你想选择的功能：\n1.计算指定日期间的天数\n2.计算指定日期是星期几\n3.打印指定日期的月历\n4.打印指定日期年历\n5.退出\n");
		scanf(" %d", &num);
		while (getchar() != '\n');
		if (num > 0 && num < 5)
		{
			printf("请输入日期，例如2025年6月2日\n");
			if (scanf("%d年%d月%d日", &year, &month, &day) != 3) {
				while (getchar() != '\n');
				printf("输入格式错误！\n");
				continue;
			}
			if (day > mon[month - 1] || is_leap_year(year) && month == 2 && day > mon[1] + 1 || month > 12 || day < 0 || month < 0 || year < 0)
			{
				printf("错误，重新输入\n");
				continue;
			}
		}
		switch (num) {
		case 1:
		{
			days = month_first_day(year, month) + day;
			printf("请输入第二个日期，例如2025年6月2日\n");
			while (scanf("%d年%d月%d日", &year, &month, &day) != 3) {
				while (getchar() != '\n');
				printf("输入格式错误2！\n");
				continue;
			}
			days = days - (month_first_day(year, month) + day);
			days = days < 0 ? -days : days;
			printf("计算指定日期间的天数差为%d\n", days);
			break;
		}

		case 2:
		{
			printf("%d年%d月%d日是 %s\n", year, month, day, week_day[(month_first_day(year, month) % 7 + day - 1) % 7]);
			break;
		}

		case 3:
		{
			calendar_month(year, month, day);
			break;
		}

		case 4:
		{
			for (int month = 1; month < 13; month++)
			{
				day = 1;
				printf("\n\n");
				printf("\t\t     %d年%d月\t\t\t", year, month);
				printf("\n\n");
				calendar_month(year, month, 1);
				printf("\n");
			}
			printf("\n");
			break;
		}
		default:
			break;
		}
	} while (num != 5);
	return 0;
}