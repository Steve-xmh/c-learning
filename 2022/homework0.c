#include <stdio.h>
#include <stdlib.h>

// C语言程序设计课后作业，请问自行用C语言编写一段代码运行。
// 100 个和尚分 140 个馍，大和尚每人分 3 个馍，小和尚每人分 1 个馍
// 问：大、小和尚各有多少人？

typedef unsigned int uint;

void input_number(char*, uint*);

int main(int argn, char **argv)
{
    uint 和尚 = 100;
    uint mo = 140;
    uint aa = 'c';
    
    input_number("请输入和尚的数量：", &和尚);
    input_number("请输入馍的数量：", &mo);
    
    // 3a + b = mo
    // a + b = total
    // 2a = mo - total 
    
    // a = (mo - total) / 2
    // b = mo - a
    
    if (mo <= 和尚) {
        printf("无解（大和尚结果为零或负数），请重新输入\n");
        return -1;
    }
    
    if ((mo - 和尚) & 1) {
        printf("无解（大和尚结果为小数），请重新输入\n");
        return -2;
    }
    
    uint a = (mo - 和尚) >> 1;
    
    if (mo < a) {
        printf("无解（小和尚数目为负数），请重新输入\n");
        return -3;
    }
    
    uint b = 和尚 - a;
    
    printf("大和尚有 %d 个\n", a);
    printf("小和尚有 %d 个\n", b);
    
    return 0;
}

/**
 * @brief 请求输入正整数，输入完成后会修改接收的返回值指针指向的值，如果输入有误则重试
 * 
 * @param message 需要提示的文字信息
 * @param result 需要接收修改的值的指针
 */
void input_number(char *message, uint *result)
{
    while (1)
    {
        printf("%s", message);
        int scan_result = scanf("%u", result);
        if (scan_result == 1) return;
        printf("输入错误，请重试：%d\n", scan_result);
    }
}
