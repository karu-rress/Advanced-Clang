#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct tagTree {
    int data;
    struct tagTree *left;
    struct tagTree *right;
} Tree, *PTREE;

Tree *insert(Tree *node, int data);
void search(Tree *node, int data);

int main(void) {
    Tree *root, *node;

    node = (Tree*)malloc(sizeof(Tree));
    memset(node, 0, sizeof(Tree));
    node->data = 20;
    root = node;

    insert(node, 5);
    insert(node, 10);
    insert(node, 7);

    search(root, 5);
    search(root, 30);
    search(root, 7);
}

Tree *insert(Tree *node, int data) {
    Tree **fNode = NULL;

    if (data < node->data) {
        if (*(fNode = &node->left)) {
            insert(node->left, data);
        }
    }
    else if (data > node->data) {
        if (*(fNode = &node->right)) {
            insert(node->right, data);
        }
    }

    if (fNode && *fNode == NULL) {
        Tree *new;
        new = (Tree*)malloc(sizeof(Tree));
        memset(new, 0, sizeof(Tree));

        new->data = data;
        *fNode = new;

        return new;
    }
    return NULL;
}

void search(Tree *node, int data) {
    if (data < node->data) {
        printf("%d->(left) ", node->data);
        if (node->left)
            search(node->left, data);
        else
            printf("데이터 없음\n");
    }
    else if (data > node->data) {
        printf("%d->(right) ", node->data);
        if (node->right)
            search(node->right, data);
        else
            printf("데이터 없음\n");
    }
    else {
        printf("[%d] 검색됨.\n", node->data);
    }
}