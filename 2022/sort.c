#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int number;

void swap(number *a, number *b)
{
    *a ^= *b; *b ^= *a; *a ^= *b;
}

void shuffle(number* array, size_t size)
{
    srand(clock());
    for (int i = 0; i < size; i++)
    {
        int a = rand() % size;
        int b = rand() % size;
        if (a == b) continue;
        // printf("交换 %8d <-> %-8d ", a, b);
        // printf("%8d <-> %-8d ", array[a], array[b]);
        swap(&array[a], &array[b]);
        // printf("%8d <-> %-8d\n", array[a], array[b]);
    }
}

void print_array(number* array, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%-4d", array[i]);
    }
    printf("\n");
}

int main()
{
    number* array = NULL;
    int size = 0;
    
    printf("请输入你想要排序的数组长度：");
    scanf("%d", &size);
    
    array = malloc(sizeof(number) * size);
    
    for (int i = 0; i < size; i++)
    {
        array[i] = i + 1;
    }
    
    printf("生成后\n");
    print_array(array, size);
    
    shuffle(array, size);
    
    printf("打乱后\n");
    print_array(array, size);
    
    // 开始排序
    
    for (int a = 0; a < size - 1; a++)
    {
        for (int b = 0; b < size - a - 1; b++)
        {
            if (array[b] > array[b + 1]) {
                swap(&array[b], &array[b + 1]);
            }
        }
    }
    
    printf("排序后\n");
    print_array(array, size);
    
    for (int i = 0; i < size - 1; i++) {
        swap(&array[i], &array[(i + 1) % size]);
    }
    
    printf("全体位移后\n");
    print_array(array, size);
    
    free(array);
    return 0;
}
