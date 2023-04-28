#include <stdio.h>

int max(int, int);

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

int main()
{
    int c, b = 0;
    printf("请输入第一个数字\n");
    scanf("%d", &c);
    printf("请输入第二个数字\n");
    scanf("%d", &b);
    int result = max(c, b);
    printf("最大的数字是：%d\n", result);
    return 0;
}
