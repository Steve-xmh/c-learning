#include <stdio.h>

int sum(int k)
{
    int x=0;
    return (x+=k);
}

int main()
{
    int s,i;
    for(i=1;i<=10;i++)
        s=sum(i);
    printf("s=%d\n",s);
}