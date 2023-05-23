#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEX_LEN (64)

int node_list[MAX_VEX_LEN];
int conn_table[MAX_VEX_LEN][MAX_VEX_LEN];

int main(void)
{
    int vertex = 0, edges = 0;
    while (scanf("%d %d", &vertex, &edges) != EOF && vertex != 0 && edges != 0)
    {

        for (int i = 0; i < edges; i++)
        {
            int from_node, connect_to;
            scanf("%d %d", &from_node, &connect_to);

            node_list[from_node] = 1;
            node_list[connect_to] = 1;

            conn_table[from_node][connect_to] = 1;
            conn_table[connect_to][from_node] = 1;
        }
        int new_vertex = 0;
        scanf("%d", &new_vertex);
        node_list[new_vertex] = 1;

        printf("0");
        for (size_t y = 1; y < MAX_VEX_LEN; y++)
        {
            if (node_list[y] == 1)
            {
                printf(" %ld", y);
            }
        }
        printf("\n");

        for (size_t y = 1; y < MAX_VEX_LEN; y++)
        {
            if (node_list[y] == 1)
            {
                printf("%ld", y);

                for (size_t x = 1; x < MAX_VEX_LEN; x++)
                {
                    if (node_list[x] == 1)
                    {
                        printf(" %d", conn_table[x][y]);
                    }
                }

                printf("\n");
            }
        }

        memset(node_list, 0, sizeof(node_list));
        memset(conn_table, 0, sizeof(conn_table));
    }
    return 0;
}
