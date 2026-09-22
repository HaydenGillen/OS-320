#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main()
{
    struct node_t *stack = NULL;
    char result[20];
    push(&stack, "cat");
    push(&stack, "a");
    pop(&stack, result);
    printf("%s\n", result);
    push(&stack, "swing");
    push(&stack,"can't");
    dump(stack);
    while(stack != NULL)
    {
        pop(&stack, result);
        printf("%s\n", result);
    }
    printf("finished!\n");
}