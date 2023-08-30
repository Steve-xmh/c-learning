#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _CityPath
{
    char city;
    int length;
    struct _CityPath *next;
} CityPath;

#define FLAG_ACCESSED (1)    // 该节点已经被访问

typedef struct City
{
    char city;
    char flags;
    int total_length;
    char *path;
    CityPath *edge;
} City;

void free_city_path(CityPath *city_path)
{
    if (city_path == NULL)
        return;
    free_city_path(city_path->next);
    free(city_path);
}

int main(void)
{
    int city_amount = 0;
    int path_amount = 0;
    while (scanf(" %d %d", &city_amount, &path_amount), city_amount != 0 && path_amount != 0)
    {
        // 输入数据
        City *cities = (City *)malloc(sizeof(City) * city_amount);
        memset(cities, 0, sizeof(City) * city_amount);
        for (int i = 0; i < city_amount; i++)
        {
            scanf(" %c", &cities[i].city);
            cities[i].total_length = -1;
        }

        for (int i = 0; i < path_amount; i++)
        {
            char from = 0;
            char to = 0;
            int length = 0;
            scanf(" %c %c %d", &from, &to, &length);
            CityPath *new_path_from = (CityPath *)malloc(sizeof(CityPath));
            CityPath *new_path_to = (CityPath *)malloc(sizeof(CityPath));
            new_path_from->city = to;
            new_path_from->length = length;
            new_path_to->city = from;
            new_path_to->length = length;
            for (int j = 0; j < city_amount; j++)
            {
                if (cities[j].city == from)
                {
                    new_path_from->next = cities[j].edge;
                    cities[j].edge = new_path_from;
                    break;
                }
            }
            for (int j = 0; j < city_amount; j++)
            {
                if (cities[j].city == to)
                {
                    new_path_to->next = cities[j].edge;
                    cities[j].edge = new_path_to;
                    break;
                }
            }
        }

        size_t from = 0; // 初始节点
        size_t to = 0;   // 目的节点
        {
            char from_tmp = 0;
            char to_tmp = 0;
            scanf(" %c %c", &from_tmp, &to_tmp);
            for (int i = 0; i < city_amount; i++)
            {
                if (cities[i].city == from_tmp)
                {
                    from = i;
                    cities[from].flags |= FLAG_ACCESSED;
                    cities[from].total_length = 0;
                    cities[from].path = (char *)malloc(sizeof(char) * 2);
                    cities[from].path[0] = from_tmp;
                    cities[from].path[1] = '\0';
                    break;
                }
            }
            for (int i = 0; i < city_amount; i++)
            {
                if (cities[i].city == to_tmp)
                {
                    to = i;
                    break;
                }
            }
        }
        
        // 通过 Djskstra 算法计算最短路径
        while (!(cities[to].flags && FLAG_ACCESSED))
        {
            // 找到当前与已访问节点直接连接的节点
            int smallest_length = -1;
            size_t from_index = (size_t)-1;
            size_t smallest_index = (size_t)-1;
            for (int i = 0; i < city_amount; i++)
            {
                if (cities[i].flags & FLAG_ACCESSED)
                {
                    CityPath *path = cities[i].edge;
                    while (path != NULL)
                    {
                        for (int j = 0; j < city_amount; j++)
                        {
                            if (cities[j].city == path->city && !(cities[j].flags & FLAG_ACCESSED))
                            {
                                if (smallest_length == -1 || smallest_length > cities[i].total_length + path->length)
                                {
                                    smallest_length = cities[i].total_length + path->length;
                                    smallest_index = j;
                                    from_index = i;
                                }
                                break;
                            }
                        }
                        path = path->next;
                    }
                }
            }
            if (smallest_index == (size_t)-1)
                break; // 没有找到最短路径
            cities[smallest_index].flags |= FLAG_ACCESSED;
            cities[smallest_index].total_length = smallest_length;
            // 拼接出从初始节点到当前节点的路径字符串
            size_t path_len = strlen(cities[from_index].path);
            if (cities[smallest_index].path == NULL)
                cities[smallest_index].path = (char *)malloc(sizeof(char) * (path_len + 2));
            for (size_t i = 0; i < path_len; i++)
                cities[smallest_index].path[i] = cities[from_index].path[i];
            cities[smallest_index].path[path_len] = cities[smallest_index].city;
            cities[smallest_index].path[path_len + 1] = '\0';
        }

        printf("%d\n", cities[to].total_length);
        if (cities[to].path != NULL)
        {
            for (size_t i = 0; i < strlen(cities[to].path); i++)
            {
                if (i) printf(" ");
                printf("%c", cities[to].path[i]);
            }
        }
        printf("\n");

        for (int i = 0; i < city_amount; i++)
            free_city_path(cities[i].edge);
        free(cities);
    }
    return 0;
}
