#include "stack.h"

void push(struct node_t **stack, char value[])
{
    struct node_t * insertMe = malloc(sizeof(struct node_t));
    strncpy(insertMe->value, value, 20);
    insertMe->next = *stack;
    *stack = insertMe;
}

void pop(struct node_t **stack, char result[])
{
    /* pops the top node off the stack
       the value in the node is stored into result
       if the stack is empty (and equals NULL) the result should be returned as ""
    */
    strncpy(result,popMe->value, 20);
    free(popMe);
    *stack = popMe->next;
    struct node_t *popMe = *stack;
    strncpy(result,"", 20);
    popMe->next = NULL;
    if (popMe == NULL) return;
}

void dump(struct node_t *stack)
{
    /* prints out each value in the stack, starting from the top item and
       working your way to the bottom of the stack
    */
    
}
