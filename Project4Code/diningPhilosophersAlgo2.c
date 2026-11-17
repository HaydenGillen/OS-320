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

Zem_t forksMutex;

//forks taken, 0 is available, not 0 is taken
int forksTaken[MAX_FORKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int numForks = 4;

void *philospher(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;
    while (1) {
        printf("Phil %d Thinking\n", id);
        sleep(id + 1);
        //only one philosopher can check forks at a time
        Zem_wait(&forksMutex);
        if (!forksTaken[id] && !forksTaken[(id + 1) % numForks]){
            forksTaken[id] = 1;
            sleep(1);
            forksTaken[(id + 1) % numForks] = 1;
        }
        Zem_post(&forksMutex);

        printf("Phil %d Eating\n", id);
        sleep(2);

        Zem_wait(&forksMutex);
        forksTaken[id] = 0;
        sleep(1);
        forksTaken[(id + 1) % numForks] = 0;
        Zem_post(&forksMutex);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        numForks = atoi(argv[1]);
    }

    Zem_init(&forksMutex, 1);
    printf("Philosphers: begin\n");
    for (int i = 0; i < numForks; ++i) {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, philospher, (void *)me);
    }

    while (1);

    return 0;
}

