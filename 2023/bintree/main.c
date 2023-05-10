#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"

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

int main()
{
    char buf[64] = {0};

    while (1)
    {
        scanf("%s", buf);
        if (strcmp(buf, "0") == 0)
            break;
        size_t tmp_index = 0;
        BTreeNode *btree = btree_build_node_dlr(buf, &tmp_index);
        size_t depth = btree_node_depth(btree);
        size_t amount = btree_node_count(btree);
        printf("%ld %ld\n", (long)depth, (long)amount);
        btree_node_free(btree);
    }

    return 0;
}