/**
 * @file vector.h
 * @author Steve Xiao (stevexmh@qq.com)
 * @brief 一个动态数组类
 * @date 2023-05-09
 */

#ifndef H_VECTOR
#define H_VECTOR

#include <stdlib.h>
#include <string.h>

typedef struct Vector
{
    void **data;
    size_t size;
    size_t capacity;
} Vector;

Vector *vector_new(void);
void vector_free(Vector *v);
void vector_expand(Vector *v, size_t capacity);
void vector_push_back(Vector *v, void *data);
void *vector_pop_back(Vector *v);
void *vector_remove(Vector *v, size_t index);
void *vector_get(Vector *v, size_t index);
int vector_set(Vector *v, size_t index, void *data);

#endif // H_VECTOR
