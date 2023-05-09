/**
 * @file bintree.h
 * @author Steve Xiao (stevexmh@qq.com)
 * @brief 一个简易的二叉树数据类型，提供了一些简易的操作方式
 */

#ifndef H_BINTREE
#define H_BINTREE

#include <stdio.h>
#include <stdlib.h>

// 因为作业要求不高，所以类型就一个整数就好
typedef int ElemType;

typedef struct BTreeNode
{
    ElemType value;
    int weight;
    struct BTreeNode *left;
    struct BTreeNode *right;
} BTreeNode;

BTreeNode *btree_node_new()
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = 0;
    node->weight = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTreeNode *btree_node_new_v(ElemType v)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = v;
    node->weight = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTreeNode *btree_node_new_lr(ElemType v, BTreeNode *left, BTreeNode *right)
{
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->value = v;
    node->weight = 0;
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

size_t btree_node_depth(BTreeNode *node)
{
    if (node == NULL)
        return 0;
    size_t ld = btree_node_depth(node->left);
    size_t rd = btree_node_depth(node->right);
    return ld > rd ? ld + 1 : rd + 1;
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

static int btree_node_is_complete_per_node(BTreeNode *node, size_t index, size_t nodes_count)
{
    if (node == NULL)
        return 0;
    if (index >= nodes_count)
        return 0;

    return 1 + btree_node_is_complete_per_node(node->left, 2 * index + 1, nodes_count) + btree_node_is_complete_per_node(node->right, 2 * index + 2, nodes_count);
}

/**
 * @brief 确认某个二叉树是否是完全二叉树
 * 
 * @param node 二叉树节点（应该是根）
 * @return 是则返回 1，否则返回 0
 */
int btree_node_is_complete(BTreeNode *node)
{
    return btree_node_is_complete_per_node(node, 0, btree_node_count(node));
}

/**
 * @brief 根据中序遍历和先序遍历构建二叉树
 * 
 * @param value_ldr_list 以中序遍历列出的实际值数组
 * @param ldr_list 中序遍历数组
 * @param dlr_list 先序遍历数组
 * @param len 三个数组的长度，必须完全一样长
 * @param dlr_start 当前先序数组的头部位置，用来确定当前根节点和左右子树的项目
 * @param dlr_end 当前先序数组的尾部位置，用来确定当前根节点和左右子树的项目
 * @param ldr_start 中序遍历数组的头部位置，用来确定左右子树的范围
 * @param ldr_end 中序遍历数组的尾部位置，用来确定左右子树的范围
 * @return 构造出来的二叉树节点
 */
BTreeNode *btree_build_node_ldr_dlr_inner(
    ElemType * value_ldr_list,
    size_t * ldr_list,
    size_t * dlr_list,
    size_t len,
    size_t dlr_start,
    size_t dlr_end,
    size_t ldr_start,
    size_t ldr_end
)
{
    if (ldr_start > ldr_end || dlr_start > dlr_end) return NULL;
    
    size_t mid = -1;
    for (size_t i = ldr_start; i < ldr_end; i++)
    {
        if (ldr_list[i] == dlr_list[dlr_start]) {
            mid = i;
            break;
        }
    }
    
    if (mid == -1) return NULL;
    
    BTreeNode * node = btree_node_new_v(value_ldr_list[mid]);
    
    node->left = btree_build_node_ldr_dlr_inner(value_ldr_list, ldr_list, dlr_list, len, dlr_start + 1, mid, ldr_start, mid - 1);
    node->right = btree_build_node_ldr_dlr_inner(value_ldr_list, ldr_list, dlr_list, len, mid + 1, dlr_end, mid + 1, ldr_end);
    
    return node;
}

/**
 * @brief 根据中序遍历和先序遍历构建二叉树
 * 
 * @param value_ldr_list 以中序遍历列出的实际值数组
 * @param ldr_list 中序遍历数组
 * @param dlr_list 先序遍历数组
 * @param len 三个数组的长度，必须完全一样长
 * @return 构造出来的二叉树节点
 */
BTreeNode *btree_build_node_ldr_dlr(
    ElemType * value_ldr_list,
    size_t * ldr_list,
    size_t * dlr_list,
    size_t len
)
{
    if (len == 0) return NULL;
    return btree_build_node_ldr_dlr_inner(value_ldr_list, ldr_list, dlr_list, len, 0, len - 1, 0, len - 1);
}

/**
 * @brief 根据中序遍历和先序遍历构建二叉树
 * 
 * @param value_ldr_list 以中序遍历列出的实际值数组
 * @param ldr_list 中序遍历数组
 * @param dlr_list 后序遍历数组
 * @param len 三个数组的长度，必须完全一样长
 * @param lrd_start 当前后序数组的头部位置，用来确定当前根节点和左右子树的项目
 * @param lrd_end 当前后序数组的尾部位置，用来确定当前根节点和左右子树的项目
 * @param ldr_start 中序遍历数组的头部位置，用来确定左右子树的范围
 * @param ldr_end 中序遍历数组的尾部位置，用来确定左右子树的范围
 * @return 构造出来的二叉树节点
 */
BTreeNode *btree_build_node_ldr_lrd_inner(
    ElemType * value_ldr_list,
    size_t * ldr_list,
    size_t * lrd_list,
    size_t len,
    size_t lrd_start,
    size_t lrd_end,
    size_t ldr_start,
    size_t ldr_end
)
{
    if (ldr_start > ldr_end || lrd_start > lrd_end) return NULL;
    
    size_t mid = -1;
    for (size_t i = ldr_start; i < ldr_end; i++)
    {
        if (ldr_list[i] == lrd_list[lrd_end]) {
            mid = i;
            break;
        }
    }
    
    if (mid == -1) return NULL;
    
    BTreeNode * node = btree_node_new_v(value_ldr_list[mid]);
    
    node->left = btree_build_node_ldr_lrd_inner(value_ldr_list, ldr_list, lrd_list, len, lrd_start, mid - 1, ldr_start, mid - 1);
    node->right = btree_build_node_ldr_lrd_inner(value_ldr_list, ldr_list, lrd_list, len, mid + 1, lrd_end, mid + 1, ldr_end);
    
    return node;
}

/**
 * @brief 根据中序遍历和后序遍历构建二叉树
 * 
 * @param value_ldr_list 以中序遍历列出的实际值数组
 * @param ldr_list 中序遍历数组
 * @param lrd_list 后序遍历数组
 * @param len 三个数组的长度，必须完全一样长
 * @return 构造出来的二叉树节点
 */
BTreeNode *btree_build_node_ldr_lrd(
    ElemType * value_ldr_list,
    size_t * ldr_list,
    size_t * lrd_list,
    size_t len
)
{
    if (len == 0) return NULL;
    return btree_build_node_ldr_lrd_inner(value_ldr_list, ldr_list, lrd_list, len, 0, len - 1, 0, len - 1);
}

#endif // H_BINTREE
