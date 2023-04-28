#include <stdio.h>
#include "queue.h"

int main()
{
	Queue *q = queue_new(4);
	for (int i = 0; i < 32; i++)
	{
		queue_push(q, i);
		printf("已推入数据 %d\n", i);
		printf(" 当前队列大小: %ld 容量: %ld\n", q->size, q->capacity);
	}
	for (int i = 0; i < 40; i++)
	{
		DataType v = 0;
		if (queue_pop(q, &v)) {
			printf("已取出数据 %d\n", v);
			printf(" 当前队列大小: %ld 容量: %ld\n", q->size, q->capacity);
		} else {
			printf("队列为空，弹出失败\n");
		}
	}
	return 0;
}
