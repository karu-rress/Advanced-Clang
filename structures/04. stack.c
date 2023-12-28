
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_MAX 100

typedef struct tagStack
{
    int array[STACK_MAX];
    int top;
    int bottom;
} Stack;

Stack stack = { {0,}, STACK_MAX, };

int push(int value)
{
    if(stack.top == 0) return -1;
    stack.array[--stack.top] = value;
    return 0;
}

int pop(void)
{
    if(stack.top == STACK_MAX) return -1;
    return stack.array[stack.top++];
}

int main(void)
{
    int i;
    
    for(i=0; i<10; i++)
    {
        push(i);
    }
    
    for(i=0; i<10; i++)
    {
        printf("%d ", pop());
    }


}