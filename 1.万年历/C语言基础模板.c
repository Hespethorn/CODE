#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdbool.h>
#include"function.h"

int main(void) {
	
	do {
		printf("����������ѡ��Ĺ��ܣ�\n1.����ָ�����ڼ������\n2.����ָ�����������ڼ�\n3.��ӡָ�����ڵ�����\n4.��ӡָ����������\n5.�˳�\n");
		scanf(" %d", &num);
		while (getchar() != '\n');
		if (num > 0 && num < 5)
		{
			printf("���������ڣ�����2025��6��2��\n");
			if (scanf("%d��%d��%d��", &year, &month, &day) != 3) {
				while (getchar() != '\n');
				printf("�����ʽ����\n");
				continue;
			}
			if (day > mon[month - 1] || is_leap_year(year) && month == 2 && day > mon[1] + 1 || month > 12 || day < 0 || month < 0 || year < 0)
			{
				printf("������������\n");
				continue;
			}
		}
		switch (num) {
		case 1:
		{
			days = month_first_day(year, month) + day;
			printf("������ڶ������ڣ�����2025��6��2��\n");
			while (scanf("%d��%d��%d��", &year, &month, &day) != 3) {
				while (getchar() != '\n');
				printf("�����ʽ����2��\n");
				continue;
			}
			days = days - (month_first_day(year, month) + day);
			days = days < 0 ? -days : days;
			printf("����ָ�����ڼ��������Ϊ%d\n", days);
			break;
		}

		case 2:
		{
			printf("%d��%d��%d���� %s\n", year, month, day, week_day[(month_first_day(year, month) % 7 + day - 1) % 7]);
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
				printf("\t\t     %d��%d��\t\t\t", year, month);
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