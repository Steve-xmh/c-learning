/**
 * @file queue.h
 * @author Steve Xiao (stevexmh@qq.com)
 * @brief 一个简易的队列数据类型，提供了一些简易的操作方式
 */

#ifndef H_QUEUE
#define H_QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 要存入队列的数据类型 */
typedef int DataType;

/**
 * @brief 队列数据类型，按照惯例支持容量自动增长
 */
typedef struct {
	DataType *data;
	size_t capacity;
	size_t size;
	size_t left;
	size_t right;
} Queue;

/**
 * @brief 创建一个队列，可选默认容量
 * @param capacity 队列容量，如果为 0 则默认为 16
 * @return Queue* 创建成功则返回对应队列的指针，创建失败则返回 NULL
 */
Queue *queue_new(size_t capacity)
{
	// 检查参数是否合法
	if (!capacity) capacity = 16;
	// 分配结构本身的内存
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	if (queue == NULL) return NULL;
	// 分配存储数据的内存
	queue->data = (DataType *)malloc(capacity * sizeof(DataType));
	if (queue->data == NULL) {
		// 因为前面的结构体本身内存分配成功了，所以需要释放先前创建的内存
		free(queue);
		return NULL;
	}
	queue->capacity = capacity;
	queue->size = 0;
	queue->left = 0;
	queue->right = 0;
	return queue;
}

/**
 * @brief 销毁一个队列，释放队列所占用的内存
 * @param queue 需要销毁的队列数据结构指针
 */
void queue_free(Queue *queue)
{
	free(queue->data);
	free(queue);
}

/**
 * @brief 变更队列的容量，如果容量参数合法则会应用变更，否则则不做修改
 * @param queue 队列结构指针
 * @param capacity 需要变更后的容量大小
 * @return 变更是否成功，如果成功则返回 1 ，否则返回 0
 */
int queue_resize(Queue *queue, size_t capacity)
{
	// 检查参数是否合法
	if (queue->size > capacity || capacity == 0) return 0;
	DataType *new_data = (DataType *)malloc(capacity * sizeof(DataType));
	if (new_data == NULL) {
		return 0;
	}
	// 将原先队列的数据复制到新的队列中
	if (queue->size > 0) {
		if (queue->left < queue->right) {
			// 如果首位位置在末位位置前面，那么只要复制首位到末位这个区间的数据即可
			
			// 如图所示：
			// - - - [1 2 3 4] - - - -
			//       ^       ^
			//     末位       首位
			memcpy(new_data, queue->data + queue->left, (queue->right - queue->left) * sizeof(DataType));
		} else {
			// 如果首位位置在末位位置的后面
			// 也就是我们当前的数据从首位一直延续到了分配的内存的末位
			// 然后从分配内存的开头再延续到了末位位置
			// 因此要分别复制这两个区间的数据
			
			// 如图所示：
			// 5 6 7 ] - - - [ 1 2 3 4
			//       ^       ^
			//     末位       首位
			memcpy(new_data, queue->data + queue->left, (queue->capacity - queue->left) * sizeof(DataType));
			memcpy(new_data + (queue->right - queue->left), queue->data, queue->left * sizeof(DataType));
		}
	}
	memcpy(new_data, queue->data, queue->capacity * sizeof(DataType));
	// 记得释放之前分配的旧内存
	free(queue->data);
	queue->data = new_data;
	queue->capacity = capacity;
	// 我们是将原来的数据复制到了新内存的开头位置
	queue->left = 0;
	queue->right = queue->size;
	return 1;
}

/**
 * @brief 将指定数据推入队列，且如果容量不足则会自动增长
 * @param queue 队列结构指针
 * @param value 需要推入的数据
 */
void queue_push(Queue *queue, DataType value)
{
	// 如果大小不够了就扩容
	// 扩大原有大小的一半
	if (queue->size == queue->capacity)
		queue_resize(queue, queue->capacity + 1 + (queue->capacity >> 1));
	queue->data[queue->right++] = value;
	queue->right %= queue->capacity;
	queue->size++;
}

/**
 * @brief 弹出队列的第一个元素  
 * @param queue 队列结构指针
 * @param value 将会存储弹出的数据的指针
 * @return 如果成功则返回 1 且 value 指针指向的数据为弹出的数据，失败返回 0 且 value 参数指针指向的数据不会修改
 */
int queue_pop(Queue *queue, DataType *value)
{
	if (queue->size == 0)
		return 0;
	*value = queue->data[queue->left++];
	queue->left %= queue->capacity;
	queue->size--;
	return 1;
}

/**
 * @brief 打印当前队列的全部数据
 * @param queue 队列结构指针
 */
void queue_debug_print(Queue *queue)
{
	printf("当前队列大小: %ld 容量: %ld\n队列内容: ", queue->size, queue->capacity);
	for (size_t i = 0; i < queue->size; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

#endif // H_QUEUE