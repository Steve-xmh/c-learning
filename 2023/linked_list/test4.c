#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book
{
    char book_id[20];
    char name[50];
    float price;
} Book;

typedef struct Node
{
    Book book;
    struct Node *next;
} Node;

void BookList_init(Node *node)
{
    memset(node, 0, sizeof(Node));
}

size_t BookList_length(Node *node)
{
    Node *cur = node;
    size_t amount = 0;
    while (cur) {
        amount++;
        cur = cur->next;
    }
    return amount;
}

Node* BookList_push(Node *node, Book book)
{
    Node *cur = node;
    while (cur->next) {
        cur = cur->next;
    }
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->book = book;
    new_node->next = NULL;
    cur->next = new_node;
    return new_node;
}

void BookList_inputData(Node *node, int amount)
{
    if (amount == -1) {
        while (1) {
            Book new_book = {0};
            scanf("%s %s %f", new_book.book_id, new_book.name, &new_book.price);
            if (strcmp("0", new_book.book_id) == 0 && strcmp("0", new_book.name) == 0 && new_book.price == 0)
                break;
            BookList_push(node, new_book);
        }
    } else {
        for (int i = 0; i < amount; i++)
        {
            Book new_book = {0};
            scanf("%s %s %f", new_book.book_id, new_book.name, &new_book.price);
            BookList_push(node, new_book);
        }
    }
}

float BookList_getMaxPrice(Node *node, size_t *amount)
{
    float tmp = 0.0;
    Node *cur = node;
    while (cur) {
        if (tmp < cur->book.price) {
            tmp = cur->book.price;
        }
        cur = cur->next;
    }
    cur = node;
    while (cur) {
        if (tmp == cur->book.price) {
            (*amount)++;
        }
        cur = cur->next;
    }
    return tmp;
}

void BookList_searchForFav(Node *node, char *book_name)
{
    size_t a = 0;
    Node *cur = node;
    while (cur) {
        if (strcmp(cur->book.name, book_name) == 0)
            a++;
        cur = cur->next;
    }
    if (a == 0) {
        printf("Sorry，there is no your favourite!\n");
        return;
    }
    cur = node;
    printf("%ld\n", a);
    while (cur) {
        if (strcmp(cur->book.name, book_name) == 0)
            printf("%s %s %.2f\n", cur->book.book_id, cur->book.name, cur->book.price);
        cur = cur->next;
    }
}

int main()
{
    Node list;
    int capacity = -1;

    scanf("%d", &capacity);

    BookList_init(&list);
    BookList_inputData(&list, capacity);
    int search_times = 0;
    scanf("%d", &search_times);
    char tmp_name[50] = { 0 };
    for (int i = 0; i < search_times; i++) {
        memset(tmp_name, 0, 50);
        scanf("%s", tmp_name);
        BookList_searchForFav(list.next, tmp_name);
    }
    
    return 0;
}
