#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
    char value[20];
    struct node_t * next;
};
void push(struct node_t **stack, char value[]);
void pop(struct node_t **stack, char value[]);
void dump(struct node_t *stack);

#endif
