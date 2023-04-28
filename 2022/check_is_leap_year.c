#include <stdio.h>
int main()
{
    int year = 0, month = 0, days = 0;
    printf("请输入年份\n");
    scanf("%d", &year);
    printf("请输入月份\n");
    scanf("%d", &month);
    int is_leap = !(year % 4) && year % 100 || !(year % 400);
    if (month > 0 && month < 8) days = 30 + month % 2;
    else if (month < 13) days = 31 - month % 2;
    if (month == 2) days = is_leap ? 29 : 28;
    if (days) printf("%d 年的 %d 月有 %d 天\n", year, month, days);
    else printf("不存在这一月\n");
    return 0;
}