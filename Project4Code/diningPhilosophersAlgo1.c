//
// Created by Hayden on 11/16/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

#define MAX_FORKS 20

Zem_t forks[MAX_FORKS];
int numForks = 4;

void *philospher(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;
    while (1) {
        printf("Phil %d Thinking\n", id);
        sleep(id + 1);
        Zem_wait(&forks[id]);                       // grab left fork
        sleep(1); // this helps us get deadlock
        Zem_wait(&forks[(id + 1) % numForks]);     // grab right fork
        printf("Phil %d Eating\n", id);
        sleep(2);
        Zem_post(&forks[id]);
        sleep(1);
        Zem_post(&forks[(id + 1) % numForks]);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        numForks = atoi(argv[1]);
    }

    for (int i = 0; i < numForks; ++i) {
        Zem_init(&forks[i], 1);
    }
    printf("Philosphers: begin\n");
    for (int i = 0; i < numForks; ++i) {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, philospher, (void *)me);
    }

    while (1);

    return 0;
}

