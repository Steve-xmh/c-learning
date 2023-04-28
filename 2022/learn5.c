#include <stdio.h>

void fun(int a, int b, int c)
{
    c = a * b;
}

int main()
{
    int c;
    fun(2, 3, c);
    printf("%d\n", c);
    return 0;
}