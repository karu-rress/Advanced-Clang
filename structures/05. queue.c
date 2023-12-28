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

int put(int value)
{
    if(queue.rear == QUEUE_MAX) return -1;
    queue.array[queue.rear++] = value;
    return 0;
}

int get(void)
{
    if(queue.front == queue.rear || queue.front == QUEUE_MAX) return -1;
    return queue.array[queue.front++];
}

int main(void)
{
    int i;
    
    for(i=0; i<10; i++)
    {
        put(i);
    }
    
    for(i=0; i<10; i++)
    {
        printf("%d ", get());
    }


}