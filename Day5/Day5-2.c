/* Day6-2.c: basic use of structures as variables */
#include <stdio.h>

struct data_t
{
    int x;
    int y;
};

void movePoint(struct data_t *point, int distance)
{
    (*point).x += distance;
    point->y += distance;
}

int main()
{
    struct data_t aPoint;
    aPoint.x = 5;
    aPoint.y = 10;
    printf("Point (x,y) is (%d,%d)\n",aPoint.x, aPoint.y);
    movePoint(&aPoint, 3);
    printf("Point (x,y) is (%d,%d)\n",aPoint.x, aPoint.y);
}