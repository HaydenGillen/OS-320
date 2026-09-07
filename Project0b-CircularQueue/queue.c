#include "queue.h"

/* This method is used to initialize a variable to be tail pointer to a 
process queue. Return a pointer to the tail of an empty process queue; 
i.e. NULL. */
struct queueNode * makeEmptyQueue(){
    return NULL;
}

/* Return TRUE if the queue whose tail is pointed to by q is empty.
Return FALSE otherwise. */
int emptyQ(struct queueNode *q){
    if(q == NULL) return TRUE;
    return FALSE;
}

/* Insert the queueNode pointed to by p into the queue whose 
tail-pointer is pointed to by q. */
void insertQ(struct queueNode **q, struct queueNode *p){
    if (*q == NULL) {
        // first item inserted points back to itself
        p->next = p;
        *q = p;
    }
    else {
        p->next = (*q)->next;
        (*q)->next = p;
        *q = p;
    }
} 

/* Remove the first (i.e. head) element from the queue whose 
tail-pointer is pointed to by q. Return NULL if the queue is empty; 
otherwise return the pointer to the removed queueNode. Update the 
queue’s tail pointer if necessary. (Note: since *q is a pointer to the tail,
(*q)->next is the head, if it exists)*/
struct queueNode *removeQ(struct queueNode **q){
    if (*q == NULL) {
        return NULL;
    }
    // if it's the last node point the queue to NULL
    else if ((*q)->next == *q){
        struct queueNode* result = *q;
        result->next = NULL;
        *q = NULL;
        return result;
    }
    else {
        struct queueNode* result = (*q)->next;
        (*q)->next = (*q)->next->next;
        // ensure the returned node doesn't point back into the queue
        result->next = NULL;
        return result;
    }
}

/* Return a pointer to the first queueNode from the queue whose tail is 
pointed to by q. Do not remove this queueNode from the queue. Return NULL 
if the queue is empty. */
struct queueNode *headQ(struct queueNode *q){
    if(q == NULL) return NULL;
    return q->next;
}