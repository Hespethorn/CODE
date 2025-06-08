#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdbool.h>
#include"function.h"
const int mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
const char *week_day[7] = { "����", "��һ", "�ܶ�", "����", "����", "����", "����" };
int year, month, day, num, days;
bool is_leap_year(int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

//�����³�
int month_first_day(int year, int month) {
	int day = 1;
	// �����׼���ۼ�����    
	day += (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	// ��������    
	if (is_leap_year(year) && month > 2) day++;
	// �·��ۼ�   
	while (--month) day += mon[month - 1];
	return day;
}
//��ӡ����
void calendar_month(int year, int month, int day)
{
	printf("��\tһ\t��\t��\t��\t��\t��\n");
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