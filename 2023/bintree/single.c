#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file bintree.h
 * @author Steve Xiao (stevexmh@qq.com)
 * @brief 一个简易的二叉树数据类型，提供了一些简易的操作方式
 */

typedef char ElemType;

typedef struct BTreeNode
{
    ElemType value;
    struct BTreeNode *left;
    struct BTreeNode *right;
} BTreeNode;

BTreeNode *btree_node_new()
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTreeNode *btree_node_new_v(ElemType v)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = v;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTreeNode *btree_node_new_lr(ElemType v, BTreeNode *left, BTreeNode *right)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = v;
    node->left = left;
    node->right = right;
    return node;
}

void btree_node_free(BTreeNode *node)
{
    if (node != NULL)
    {
        btree_node_free(node->left);
        btree_node_free(node->right);
        free(node);
    }
}

size_t btree_node_count(BTreeNode *node)
{
    if (node == NULL)
        return 0;
    return 1 + btree_node_count(node->left) + btree_node_count(node->right);
}

/**
 * @brief 确认某个二叉树节点是否是满二叉树
 *
 * @param node 二叉树节点（应该是根）
 */
int btree_node_is_full(BTreeNode *node)
{
    if (node == NULL)
        return 1;
    int left_is_full = node->left && btree_node_is_full(node->left);
    int right_is_full = node->right && btree_node_is_full(node->right);
    return left_is_full && right_is_full;
}

BTreeNode *btree_build_node_dlr(char *data, size_t *index)
{
    if (data[*index] == '0')
    {
        return NULL;
    }
    else
    {
        BTreeNode *node = btree_node_new_v(data[*index]);
        (*index)++;
        node->left = btree_build_node_dlr(data, index);
        (*index)++;
        node->right = btree_build_node_dlr(data, index);
        return node;
    }
}

size_t btree_get_degree(BTreeNode *node)
{
    if (node == NULL)
        return 0;
    size_t result = 0;
    if (node->left != NULL)
        result++;
    if (node->right != NULL)
        result++;
    return result;
}

void btree_count_degree_typed(BTreeNode *node, size_t *zero_degree, size_t *one_degree, size_t *two_degree)
{
    if (node == NULL)
        return;
    switch (btree_get_degree(node))
    {
    case 0:
        (*zero_degree)++;
        break;
    case 1:
        (*one_degree)++;
        break;
    case 2:
        (*two_degree)++;
        break;
    default:
        break;
    }
    btree_count_degree_typed(node->left, zero_degree, one_degree, two_degree);
    btree_count_degree_typed(node->right, zero_degree, one_degree, two_degree);
}

int main()
{
    char buf[64] = {0};

    while (1)
    {
        if (scanf("%s", buf) == EOF)
            continue;
        if (strcmp(buf, "0") == 0)
            break;
        size_t tmp_index = 0;
        BTreeNode *btree = btree_build_node_dlr(buf, &tmp_index);
        size_t zero_degree = 0, one_degree = 0, two_degree = 0;
        btree_count_degree_typed(btree, &zero_degree, &one_degree, &two_degree);
        printf("%ld %ld %ld\n", (long)zero_degree, (long)one_degree, (long)two_degree);
        btree_node_free(btree);
    }

    return 0;
}