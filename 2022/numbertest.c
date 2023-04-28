#include <stdio.h>

int main(int argn, char** argv)
{
    long int input;
    
    scanf("%ld", &input);
    
    long int a = input;
    long int b = (input - input % 10) / 10;
    long int c = (input - input % 100) / 100;
    
    printf("个位是 %ld 十位是 %ld 百位是 %ld\n", a % 10, b % 10, c % 10);
    return 0;
}