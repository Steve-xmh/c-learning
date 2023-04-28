// #include <stdio.h>
int main()
{
    // 编写程序，输出如下的图形
    //  1
    //  2   4
    //  3   6   9
    //  4   8   12  16
    //  5   10  15  20  25
    //  6   12  18  24  30  36
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= i; j++) {
            // printf("%d\t", i * j);
        }
        // printf("\n");
    }
    return 0;
}