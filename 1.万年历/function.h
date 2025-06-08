#ifndef  FUNCTION_H
#define FUNCTION_H
extern int year, month, day, num, days;
extern const int mon[12];
extern const char *week_day[7];

bool is_leap_year(int year);
int month_first_day(int year, int month);
void calendar_month(int year, int month, int day);
#endif // ! FUNCTION_H