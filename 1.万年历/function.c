#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdbool.h>
#include"function.h"
const int mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const char *week_day[7] = { "周日", "周一", "周二", "周三", "周四", "周五", "周六" };
int year, month, day, num, days;
bool is_leap_year(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

//计算月初
int month_first_day(int year, int month) {
	int day = 1;
	// 计算基准日累计天数    
	day += (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	// 闰年修正    
	if (is_leap_year(year) && month > 2) day++;
	// 月份累计   
	while (--month) day += mon[month - 1];
	return day;
}
//打印月历
void calendar_month(int year, int month, int day)
{
	printf("日\t一\t二\t三\t四\t五\t六\n");
	for (int i = 0; i < 51; i++) {
		printf("=");
	}
	printf("\n");

	for (int i = 0; i < month_first_day(year, month) % 7; i++)
	{
		printf("\t");
	}
	for (int d = 1; d <= mon[month - 1]; d++)
	{
		printf("%d\t", d);
		if ((month_first_day(year, month) % 7 + d) % 7 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
	for (int i = 0; i < 51; i++) {
		printf("=");
	}
	printf("\n");
}