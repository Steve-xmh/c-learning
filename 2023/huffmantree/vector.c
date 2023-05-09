#include "vector.h"

Vector *vector_new(void)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->data = (void **)malloc(16 * sizeof(void *));
    v->size = 0;
    v->capacity = 16;
    return v;
}

void vector_free(Vector *v)
{
    for (size_t i = 0; i < v->size; i++)
    {
        free(v->data[i]);
    }
    free(v->data);
    free(v);
}

void vector_clear(Vector *v)
{
    v->size = 0;
}

void vector_expand(Vector *v, size_t capacity)
{
    if (v->size > capacity)
        return;
    if (v->data == NULL)
    {
        v->data = (void **)malloc(capacity * sizeof(void *));
    }
    else
    {
        v->data = (void **)realloc(v->data, capacity * sizeof(void *));
    }
    v->capacity = capacity;
}

void vector_push_back(Vector *v, void *data)
{
    if (v->size >= v->capacity)
    {
        vector_expand(v, 2 * v->capacity);
    }
    v->data[v->size++] = data;
}

void *vector_pop_back(Vector *v)
{
    return v->data[--v->size];
}

void *vector_remove(Vector *v, size_t index)
{
    void *data = v->data[index];
    memmove(v->data + index, v->data + index + 1, (v->size - index - 1) * sizeof(void *));
    v->size--;
    return data;
}

void *vector_get(Vector *v, size_t index)
{
    return v->data[index];
}

int vector_set(Vector *v, size_t index, void *data)
{
    if (index >= v->size)
        return 0;
    v->data[index] = data;
    return 1;
}
