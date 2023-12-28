#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode {
    int data;
    struct tagNode *next;
    struct tagNode *prev;
} Node;

int main(void) {
    Node *node, *head = NULL, *tail = NULL, *pn = NULL;

    node = (Node*)malloc(sizeof(Node));
    node->data = 100;
    node->prev = NULL;
    node->next = NULL;
    head = tail = node;

    node = (Node*)malloc(sizeof(Node));
    node->data = 200;
    node->prev = tail;
    node->next = NULL;
    tail->next = node;
    pn = tail = node;

    node = (Node*)malloc(sizeof(Node));
    node->data = 300;
    node->prev = tail;
    node->next = NULL;
    tail->next = node;
    tail = node;

    for (node = head; node; node = node->next) {
        printf("%d\n", node->data);
    }

    for (node = tail; node; node = node->prev) {
        printf("%d\n", node->data);
    }

    // Adding node
    node = (Node*)malloc(sizeof(Node));
    node->data = 0;
    node->next = head;
    node->prev = NULL;
    head->prev = node;
    head = node;

    node = (Node*)malloc(sizeof(Node));
    node->data = 250;
    node->next = pn->next;
    node->prev = pn;

    pn->next->prev = node;
    pn->next = node;

    // Deleting node
    node = head;
    head = head->next;
    head->prev = NULL;

    if (!head) tail = NULL;
    free(node);

    node = tail;
    tail = tail->prev;
    tail->next = NULL;

    if (!tail) head = NULL;
    free(node);

    node = pn->prev;
    node->next = pn->next;
    node = pn->next;
    node->prev = pn->prev;
    free(pn);


    node = head;
    while (node) {
        Node *next = node->next;
        free(node);
        node = next;
    }
}