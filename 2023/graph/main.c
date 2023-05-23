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
    int access_count;
    ArcNode *first_arc;
} VexNode;

#define MAX_VEX_LEN (64)

VexNode vexlist[MAX_VEX_LEN];

int main(void)
{
    int vertex = 0, edges = 0;
    while (scanf("%d %d", &vertex, &edges) != EOF && vertex != 0 && edges != 0)
    {
        for (size_t i = 0; i < MAX_VEX_LEN; i++)
        {
            vexlist[i].access_count = -1;
            vexlist[i].first_arc = NULL;
        }

        for (int i = 0; i < edges; i++)
        {
            int from_node, connect_to;
            scanf("%d %d", &from_node, &connect_to);

            ArcNode *arc = (ArcNode *)malloc(sizeof(ArcNode));
            arc->vextex = connect_to;
            arc->next = vexlist[from_node].first_arc;
            vexlist[from_node].access_count = 0;
            vexlist[from_node].first_arc = arc;

            arc = (ArcNode *)malloc(sizeof(ArcNode));
            arc->vextex = from_node;
            arc->next = vexlist[connect_to].first_arc;
            vexlist[connect_to].access_count = 0;
            vexlist[connect_to].first_arc = arc;
        }
        int new_vertex = 0;
        scanf("%d", &new_vertex);

        vexlist[new_vertex].access_count = 0;

        for (size_t i = 0; i < MAX_VEX_LEN; i++)
        {
            if (vexlist[i].access_count == -1)
                continue;
            printf("%ld", i);
            ArcNode *arc = vexlist[i].first_arc;
            while (arc != NULL)
            {
                printf(" %d", arc->vextex);
                arc = arc->next;
            }
            printf("\n");
        }
    }
    return 0;
}
