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

int BookList_removeData(Node *node, size_t pos)
{
    Node *parent = node;
    Node *cur = node;
    if (pos < 0) {
        return 0;
    }
    for (size_t i = 1; i < pos; i++) {
        parent = cur;
        cur = cur->next;
        if (!cur) return 0;
    }
    parent->next = cur->next;
    free(cur);
    return 1;
}

void BookList_outputData(Node *node)
{
    Node *cur = node;
    while (cur) {
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
    size_t remove_pos = 0;
    scanf("%ld", &remove_pos);
    
    if (BookList_removeData(list.next, remove_pos)) {
        BookList_outputData(list.next);
    } else {
        printf("Sorry，the position to be deleted is invalid!\n");
    }
    
    return 0;
}
