#include <stdio.h>
int main()
{
    // 小明有 5 本新书，要借给 A B C 三位小朋友，若每人每次只能借一本，共有多少种借书的方案？
    int method_id = 0;
    
    // 假设我们给 5 本书编号，分别是 1 号到 5 号书本
    // 然后三位小朋友会借到其中的一本，那么我们以每个小朋友为循环，判断他们借到的书本是否冲突
    // 如果不冲突，那么就是一个可行的方案
    for (int a = 1; a <= 5; a++) {
        for (int b = 1; b <= 5; b++) {
            for (int c = 1; c <= 5; c++) {
                // 如果遇到借了同一本书则忽略这个方案，继续循环
                if (a == b || b == c || a == c) {
                    continue;
                }
                method_id++; // 方案编号加一
                printf("方案 %d: A 会借到 %d 号书，B 会借到 %d 号书，C 会借到 %d 号书\n", method_id, a, b, c);
            }
        }
    }
    
    printf("总共有 %d 个借书方案\n", method_id);
    
    return 0;
}