#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode {
    int data;
    struct tagNode *next;
} Node;

int main(void) {
    Node *node, *head = NULL, *tail = NULL;

    node = (Node*)malloc(sizeof(Node));
    node->data = 100;
    node->next = NULL;
    head = tail = node;

    node = (Node*)malloc(sizeof(Node));
    node->data = 200;
    node->next = NULL;
    tail->next = node;
    tail = node;

    node = (Node*)malloc(sizeof(Node));
    node->data = 300;
    node->next = NULL;
    tail->next = node;
    tail = node;

    for (node = head; node != NULL; node = node->next) {
        printf("%d\n", node->data);
    }

    node = head;
    Node *next;
    while (node) {
        next = node->next;
        free(node);
        node = next;
    }
}