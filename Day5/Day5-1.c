/* Example C code adapted from Dive into Systems (thanks Tia!) */
#include <stdio.h>

int change(int *changeMe, int byThisAmount);

int main(void) {
    int x, result;   /* local variables: declared inside function bodies */

    printf("Enter a value: ");
    scanf("%d", &x);

    result = change(&x, 10);
    printf("x's value was %d and now is %d\n", result, x);

    return 0;
}

int change(int * changeMe, int byThisAmount) {
    int val;

    val = *changeMe; /* the value before change */
    *changeMe += byThisAmount;
    return val;
}