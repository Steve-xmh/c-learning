#include <stdio.h>
#include <string.h>

int index_of(char s[], char t[])
{
    int i = 0;
    int j = 0;
    while (i < strlen(s) && j < strlen(t))
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i + 1;
            j = 0;
        }
    }
    if (j == strlen(t))
    {
        return i - strlen(t);
    }
    else
    {
        return -1;
    }
}

int main()
{
    int i = index_of("abcdefg", "cde");
    printf("Test: %d\n", i);
    return 0;
}
