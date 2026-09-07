#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#define ITEMS_TO_ADD 10

void printQueue(struct queueNode* q);
void addNItems(struct queueNode** q, int n);
void popNItems(struct queueNode** q, int n); // negative int empties the queue
void printEmptyState(struct queueNode* q);

int main(){
    struct queueNode* myQueue = makeEmptyQueue();

    printEmptyState(myQueue);
  
    addNItems(&myQueue, 10);

    printEmptyState(myQueue);

    printQueue(myQueue);

    popNItems(&myQueue, 5);
    addNItems(&myQueue, 7);
    popNItems(&myQueue, -1);

    printEmptyState(myQueue);
}

void printQueue(struct queueNode* q){
    if (q == NULL) return;
    struct queueNode* curr = q;

    puts("Everything in Queue: ");
    do {
        curr = curr->next;
        printf("%d \n", curr->value.data);
    } while (curr != q);    
}

void addNItems(struct queueNode** q, int n){
    if (n < 0) return;
    for (int i = 0; i < n; i++){
        struct queueNode* curr = malloc(sizeof(struct queueNode));
        curr->value.data = i;
        printf("+enqueue %p: %d\n", curr, curr->value.data);
        insertQ(q, curr);
    }
}

void popNItems(struct queueNode** q, int n){
    struct queueNode* curr;
    if (n < 0){
        while (!emptyQ(*q)) {
            curr = removeQ(q);
            printf("-dequeue %p: %d \n", curr, curr->value.data);
            free(curr);
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            curr = removeQ(q);
            if (curr == NULL) return;
            printf("dequeue %p: %d \n", curr, curr->value.data);
            free(curr);
        }
    }
}

void printEmptyState(struct queueNode* q){
    if (emptyQ(q)) puts("Empty");
    else puts("Not Empty");
}