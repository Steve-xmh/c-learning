#include <stdio.h>

void fun1(int n, int a[][3])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = a[i][j] / a[i][i];
}

int main()
{
    int a[3][3] = {{6, 4, 2}, {8, 6, 4}, {9, 6, 3}};
    fun1(3, a);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf("%d ", a[i][j]);
        printf("\n");
    }
    return 0;
}
