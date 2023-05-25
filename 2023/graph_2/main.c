#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _ArcNode
{
    int vextex;
    struct _ArcNode *next;
} ArcNode;

typedef struct
{
    double relation_aspect;
    ArcNode *first_arc;
} VexNode;

int main(void)
{
    int people = 0, relations = 0;
    VexNode *vex_nodes = NULL;

    while (scanf("%d %d", &people, &relations) != EOF && people != 0 && relations != 0)
    {
        vex_nodes = (VexNode *)malloc(sizeof(VexNode) * people);
        memset(vex_nodes, 0, sizeof(VexNode) * people);
        for (int i = 0; i < relations; i++)
        {
            int from_node, connect_to;
            scanf("%d %d", &from_node, &connect_to);
            from_node--;
            connect_to--;
            ArcNode *arc = (ArcNode *)malloc(sizeof(ArcNode));
            arc->vextex = connect_to;
            arc->next = vex_nodes[from_node].first_arc;
            vex_nodes[from_node].first_arc = arc;
            arc = (ArcNode *)malloc(sizeof(ArcNode));
            arc->vextex = from_node;
            arc->next = vex_nodes[connect_to].first_arc;
            vex_nodes[connect_to].first_arc = arc;
        }

        // 计算六度
        // 本质上就是一种寻路算法
        int *iter_nodes = (int *)malloc(sizeof(int) * people); // 记录已经遍历完了的节点
        int iter_nodes_len = 0;
        int *tmp = (int *)malloc(sizeof(int) * people);
        int tmp_len = 0;

        for (int src_i = 0; src_i < people; src_i++)
        {
            memset(iter_nodes, 0, sizeof(int) * people);
            iter_nodes_len = 0;

            iter_nodes[iter_nodes_len++] = src_i;

            // 循环扩散
            for (int iter_i = 0; iter_i < 6; iter_i++)
            {
                memcpy(tmp, iter_nodes, sizeof(int) * people);
                tmp_len = iter_nodes_len;
                for (int j = 0; j < tmp_len; j++)
                {
                    ArcNode *arc = vex_nodes[tmp[j]].first_arc;
                    while (arc != NULL)
                    {
                        int should_add = 1;
                        for (int j = 0; j < iter_nodes_len; j++)
                        {
                            if (iter_nodes[j] == arc->vextex)
                            {
                                should_add = 0;
                                break;
                            }
                        }
                        if (should_add)
                        {
                            iter_nodes[iter_nodes_len++] = arc->vextex;
                        }
                        arc = arc->next;
                    }
                }
            }

            vex_nodes[src_i].relation_aspect = (double)iter_nodes_len / (double)people;
        }
        free(iter_nodes);
        free(tmp);

        // 打印结果
        for (int i = 0; i < people; i++)
        {
            printf("%d: %.02f%%\n", i + 1, vex_nodes[i].relation_aspect * 100);
        }

        for (int i = 0; i < people; i++)
        {
            ArcNode *arc = vex_nodes[i].first_arc;
            while (arc != NULL)
            {
                ArcNode *next = arc->next;
                free(arc);
                arc = next;
            }
        }
        free(vex_nodes);
    }

    return 0;
}
