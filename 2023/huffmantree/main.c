#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "vector.h"

typedef struct HTreeNode
{
    int weight;
    size_t left;
    size_t right;
} HTreeNode;

HTreeNode *new_node(int weight)
{
    HTreeNode *node = (HTreeNode *)malloc(sizeof(HTreeNode));
    node->weight = weight;
    node->left = SIZE_MAX;
    node->right = SIZE_MAX;
    return node;
}

void free_node(HTreeNode *node)
{
    free(node);
}

size_t get_node_parent(Vector *huffman_tree, size_t node_index)
{
    if (node_index == SIZE_MAX)
        return SIZE_MAX;
    for (size_t i = 0; i < huffman_tree->size; i++)
    {
        HTreeNode *node = (HTreeNode *)huffman_tree->data[i];
        if (node->left == node_index || node->right == node_index)
            return i;
    }
    return SIZE_MAX;
}

size_t get_node_root(Vector *huffman_tree)
{
    for (size_t i = 0; i < huffman_tree->size; i++)
    {
        size_t parent = get_node_parent(huffman_tree, i);
        if (parent == SIZE_MAX)
            return i;
    }
    return SIZE_MAX;
}

void print_huffman_tree(Vector *huffman_tree)
{
    for (size_t i = 0; i < huffman_tree->size; i++)
    {
        HTreeNode *node = (HTreeNode *)huffman_tree->data[i];

        size_t left = node->left;
        if (left == SIZE_MAX)
            left = 0;
        else
            left++;

        size_t right = node->right;
        if (right == SIZE_MAX)
            right = 0;
        else
            right++;

        size_t parent = get_node_parent(huffman_tree, i);
        if (parent == SIZE_MAX)
            parent = 0;
        else
            parent++;

        printf("%ld %d %ld %ld %ld\n", (long)(i + 1), (long)node->weight, (long)parent, (long)left, (long)right);
    }
}

void get_huffman_encode(Vector *huffman_tree, size_t node_index, unsigned long int *result, size_t *result_size)
{
    size_t parent_index = get_node_parent(huffman_tree, node_index);
    if (parent_index == SIZE_MAX)
    {
        *result_size = 1;
    }
    while (parent_index != SIZE_MAX)
    {
        HTreeNode *parent = (HTreeNode *)huffman_tree->data[parent_index];
        if (parent->left == node_index)
        {
            (*result_size)++;
            *result <<= 1;
        }
        else if (parent->right == node_index)
        {
            (*result_size)++;
            *result <<= 1;
            *result |= 1;
        }
        else
        {
            break;
        }
        node_index = parent_index;
        parent_index = get_node_parent(huffman_tree, parent_index);
    }
}

typedef struct TempNode
{
    size_t index;
    int weight;
} TempNode;

TempNode *new_temp_node(size_t index, int weight)
{
    TempNode *node = (TempNode *)malloc(sizeof(TempNode));
    node->index = index;
    node->weight = weight;
    return node;
}

void free_temp_node(TempNode *node)
{
    free(node);
}

void print_encode(unsigned long int result, size_t result_size)
{
    for (size_t i = 0; i < result_size; i++)
    {
        printf("%ld", result & 1);
        result >>= 1;
    }
}

void print_temp_vector(Vector *v)
{
    for (size_t i = 0; i < v->size; i++)
    {
        TempNode *node = (TempNode *)v->data[i];
        printf("(%ld, %d) ", (long)(node->index + 1), (long)(node->weight));
    }
    printf("\n");
}

int main(void)
{
    char buf[64] = {0};       // 存放输入文字的缓冲区
    int code_table[27] = {0}; // 只关注 26 个小写英文字母，所以就只留 26 + 1 个字
    char codes[27] = {0};     // 按顺序存放已知字符编码

    while (1)
    {
        scanf("%s", buf);
        if (strcmp(buf, "0") == 0)
            break;

        memset(code_table, 0, sizeof(code_table));
        memset(codes, 0, sizeof(codes));

        for (size_t i = 0; i < strlen(buf); i++)
        {
            code_table[buf[i] - 'a']++;
        }
        Vector *huffman_tree = vector_new();
        Vector *tmp = vector_new();

        // 输出权值
        for (char i = 0; i < 26; i++)
        {
            int weight = code_table[(size_t)i];
            if (weight > 0)
            {
                vector_push_back(huffman_tree, new_node(weight));
                vector_push_back(tmp, new_temp_node(strlen(codes), weight));
                if (strlen(codes) != 0)
                    printf(" ");
                char cat[2] = {'a' + i, 0};
                strcat(codes, cat);
                printf("%c:%d", 'a' + i, weight);
            }
        }
        printf("\n");

        // 开始构造哈夫曼树
        while (tmp->size > 2)
        {
            // print_temp_vector(tmp); // 解除这个注释来查看每一次处理当前队列的节点

            size_t tmp_len = tmp->size;
            TempNode *node_a = (TempNode *)vector_remove(tmp, 0);
            TempNode *node_b = NULL;
            for (size_t i = 1; i < tmp_len; i++)
            {
                TempNode *temp = (TempNode *)vector_remove(tmp, 0);
                if (node_a->weight > temp->weight)
                {
                    if (node_b != NULL)
                    {
                        vector_push_back(tmp, node_b);
                    }
                    node_b = node_a;
                    node_a = temp;
                }
                else if (node_b == NULL)
                {
                    node_b = temp;
                }
                else if (node_b->weight > temp->weight)
                {
                    vector_push_back(tmp, node_b);
                    node_b = temp;
                }
                else
                {
                    vector_push_back(tmp, temp);
                }
            }
            HTreeNode *new = new_node(0);

            // printf("该轮最小的两个节点为 %ld (%d), %ld (%d)\n", node_a->index + 1, node_a->weight, node_b->index + 1, node_b->weight);

            new->weight = node_a->weight + node_b->weight;
            new->left = node_a->index;
            new->right = node_b->index;

            free_temp_node(node_a);
            free_temp_node(node_b);

            // printf("增加新节点 %d 于位置 %ld\n", new->weight, huffman_tree->size + 1);

            vector_push_back(tmp, new_temp_node(huffman_tree->size, new->weight));
            vector_push_back(huffman_tree, new);
        }

        // printf("拼接根节点\n");
        if (tmp->size == 2)
        {
            HTreeNode *root = new_node(0);
            TempNode *node_a = (TempNode *)vector_remove(tmp, 0);
            TempNode *node_b = (TempNode *)vector_remove(tmp, 0);
            root->weight = node_a->weight + node_b->weight;
            if (node_a->weight > node_b->weight)
            {
                root->left = node_b->index;
                root->right = node_a->index;
            }
            else
            {
                root->left = node_a->index;
                root->right = node_b->index;
            }
            vector_push_back(huffman_tree, root);
        }

        print_huffman_tree(huffman_tree);
        size_t longest_encode = 0;
        // 输出编码表
        for (size_t i = 0; i < strlen(codes); i++)
        {
            unsigned long int encode = 0;
            size_t encode_len = 0;
            get_huffman_encode(huffman_tree, i, &encode, &encode_len);
            if (encode_len > longest_encode)
                longest_encode = encode_len;
            if (i != 0)
                printf(" ");
            printf("%c:", codes[i]);
            print_encode(encode, encode_len);
        }
        printf("\n");
        char *result = malloc(sizeof(char) * strlen(buf) * longest_encode);
        result[0] = '\0'; // 比 memset 更方便的方式
        // 编码字符串
        for (size_t i = 0; i < strlen(buf); i++)
        {
            unsigned long int encode = 0;
            size_t encode_len = 0;
            char substr[2] = {buf[i], 0};
            size_t code_index = strstr(codes, substr) - codes;
            get_huffman_encode(huffman_tree, code_index, &encode, &encode_len);
            for (size_t j = 0; j < encode_len; j++)
            {
                if (encode & 1)
                    strcat(result, "1");
                else
                    strcat(result, "0");
                encode >>= 1;
            }
        }
        printf("%s\n", result);
        // 解码字符串
        size_t cur_index = huffman_tree->size - 1; // 最后被推入的元素应该是根
        for (size_t i = 0; i < strlen(result); i++)
        {
            HTreeNode *node = huffman_tree->data[cur_index];
            if (result[i] == '1')
            {
                cur_index = node->right;
            }
            else
            {
                cur_index = node->left;
            }
            node = huffman_tree->data[cur_index];
            if (node->left == SIZE_MAX && node->right == SIZE_MAX)
            {
                // 是叶子，也就是对应的编码字符
                printf("%c", codes[cur_index]);
                cur_index = huffman_tree->size - 1;
            }
        }

        printf("\n");

        free(result);
        vector_free(tmp);
        vector_free(huffman_tree);
    }

    return 0;
}
