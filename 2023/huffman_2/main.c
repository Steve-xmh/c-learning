
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct
{

    int weight;

    int parent, lch, rch;

} HTNode, *HuffmanTree;

void Select(HuffmanTree HT, int i, int *s1, int *s2)
{

    *s1 = *s2 = -1;

    for (int j = 1; j <= i; j++)
    {

        if (HT[j].parent == 0)
        {

            if (*s1 == -1 || HT[j].weight < HT[*s1].weight)
            {

                *s2 = *s1;

                *s1 = j;
            }
            else if (*s2 == -1 || HT[j].weight < HT[*s2].weight)
            {

                *s2 = j;
            }
        }
    }
}

void CreatHuffmanTree(HuffmanTree *HT, int n)
{

    if (n <= 1)
        return;

    int i, m, s1, s2;

    m = 2 * n - 1;

    *HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));

    for (i = 1; i <= m; ++i)
    {

        (*HT)[i].lch = 0;

        (*HT)[i].rch = 0;

        (*HT)[i].parent = 0;
    }

    for (i = 1; i <= n; ++i)
    {

        scanf("%d", &((*HT)[i].weight));
    }

    for (i = n + 1; i <= m; ++i)
    {

        Select(*HT, i - 1, &s1, &s2);

        (*HT)[s1].parent = i;

        (*HT)[s2].parent = i;

        (*HT)[i].lch = s1;

        (*HT)[i].rch = s2;

        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

void CreatHuffmanCode(HuffmanTree HT, char ***HC, int n)
{

    *HC = (char **)malloc(sizeof(char **) * (n + 1));

    char *a;

    a = (char *)malloc(sizeof(char) * n);

    a[n - 1] = '\0';

    int start, c, f;

    for (int i = 1; i <= n; i++)
    {

        start = n - 1;

        c = i;

        f = HT[i].parent;

        while (f != 0)
        {

            --start;

            if (HT[f].lch == c)
                a[start] = '0';

            else
                a[start] = '1';

            c = f;

            f = HT[f].parent;
        }

        (*HC)[i] = (char *)malloc(sizeof(char*) * (n - start + 1));

        strcpy((*HC)[i], &a[start]);
    }

    free(a);
}

void Print_m(int *m)
{

    printf("%c:%d", 'a', m[1]);

    for (int i = 2; i <= 26; i++)
    {

        if (m[i])
            printf("%c:%d", 'a' + i - 1, m[i]);
    }

    printf("\n");
}

void Print_Weights(HuffmanTree HT, int n)
{

    for (int i = n + 1; i <= 2 * n - 1; i++)
    {

        printf("%d", HT[i].weight);
    }

    printf("\n");
}

void Print_Codes(char **HC, int n)
{

    for (int i = 1; i <= n; i++)
    {

        printf("%c%s\n", 'a' + i - 1, HC[i]);
    }
}

void Encode(char *s, char **HC)
{

    for (int i = 0; i < strlen(s); i++)
    {

        printf("%s", HC[s[i] - 'a' + 1]);
    }

    printf("\n");
}

void Decode(HuffmanTree HT, char *c, int n)
{

    char *result = (char *)malloc(sizeof(char) * (strlen(c) + 1));
    int cnt = 0;
    int root = 0;

    for (int i = n + 1; i <= 2 * n - 1; i++)
    {

        if (HT[i].lch == 0 && HT[i].rch == 0)
        {

            root = i;

            break;
        }
    }

    int cur = root;

    for (int i = 0; i < strlen(c); i++)
    {

        if (c[i] == '0')
            cur = HT[cur].lch;

        else
            cur = HT[cur].rch;

        if (HT[cur].lch == 0 && HT[cur].rch == 0)
        {

            result[cnt++] = HT[cur].weight + 'a' - 1;

            cur = root;
        }
    }

    result[cnt] = '\0';

    printf("%s", result);
    
    free(result);
}

void Gethuffmancode(HuffmanTree node, char **codes, char *code, int depth)
{

    int i = 0;

    if (node->lch == NULL && node->rch == NULL)
    {

        code[depth] = '\0';

        char *new_code = (char *)malloc(sizeof(char) * (depth + 1));

        strcpy(new_code, code);

        codes[node->weight] = new_code;

        return;
    }

    if (node->lch)
    {

        code[depth] = '0';

        Gethuffmancode(node->lch, codes, code, depth + 1);
    }

    if (node->rch)
    {

        code[depth] = '1';

        Gethuffmancode(node->rch, codes, code, depth + 1);
    }
}

int main()
{

    char s[30];

    while (scanf("%s", s))
    {

        if (s[0] == '0')
            break;

        int m[27] = {0};

        for (int i = 0; i < strlen(s); i++)
        {

            m[s[i] - 'a' + 1]++;
        }

        int n = 0;

        for (int i = 1; i <= 26; i++)
        {

            if (m[i])
                n++;
        }

        Print_m(m);

        HuffmanTree HT;

        CreatHuffmanTree(&HT, n);

        char **HC = NULL;

        CreatHuffmanCode(HT, &HC, n);

        Print_Weights(HT, n);

        Print_Codes(HC, n);

        Encode(s, HC);

        char c[100];

        scanf("%s", c);

        Decode(HT, c, (n + 1) / 2);

        char *codes[27] = {NULL};

        char code[30];

        Gethuffmancode(HT, codes, code, 0);

        for (int i; i < 26; i++)
        {

            if (codes[i] != NULL)
                printf("%c:%s\n", 'a' + i - 1, codes[i]);
        }
    }

    return 0;
}