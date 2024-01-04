#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define QUEUE_MAX 100

typedef struct tagQueue
{
    int array[QUEUE_MAX];
    int front;
    int rear;
} Queue;

Queue queue = { {0,}, 0, 0 };

int enqueue(int value);
int dequeue(void);

int main(void) {
    int i;
    
    for (i = 0; i < 10; i++) 
        enqueue(i);
    
    for (i = 0; i < 10; i++) 
        printf("%d ", dequeue());

    return 0;
}

int enqueue(int value) {
    if (queue.rear == QUEUE_MAX) return -1;
    queue.array[queue.rear++] = value;
    return 0;
}

int dequeue(void) {
    if (queue.front == queue.rear || queue.front == QUEUE_MAX) return -1;
    return queue.array[queue.front++];
}