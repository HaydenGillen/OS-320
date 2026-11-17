//
// Created by Hayden on 11/16/2026.
//
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
Zem_t forksTakenMutex;
int forksTaken[MAX_FORKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int numForks = 4;

void *philospher(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;
    while (1) {
        printf("Phil %d Thinking\n", id);
        sleep(id + 1);

        Zem_wait(&forks[id]);                       // grab left fork
        Zem_wait(&forksTakenMutex);
        forksTaken[id] = 1;
        Zem_post(&forksTakenMutex);

        sleep(1); // this helps us get deadlock

        Zem_wait(&forks[(id + 1) % numForks]);     // grab right fork
        Zem_wait(&forksTakenMutex);
        forksTaken[(id + 1) % numForks] = 1;
        Zem_post(&forksTakenMutex);

        printf("Phil %d Eating\n", id);
        sleep(2);

        Zem_wait(&forksTakenMutex);
        forksTaken[id] = 0;
        Zem_post(&forksTakenMutex);
        Zem_post(&forks[id]);

        sleep(1);

        Zem_wait(&forksTakenMutex);
        forksTaken[(id + 1) % numForks] = 0;
        Zem_post(&forksTakenMutex);
        Zem_post(&forks[(id + 1) % numForks]);
    }
}

void *roguePhilospher(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;
    while (1) {
        printf("Phil %d Thinking\n", id);
        sleep(id + 1);
        Zem_wait(&forks[id]);                       // grab left fork
        Zem_wait(&forksTakenMutex);
        forksTaken[id] = 1;
        Zem_post(&forksTakenMutex);

        sleep(1); // this helps us get deadlock

        Zem_wait(&forksTakenMutex);                 // grab whichever fork is available
        int i = 0;
        while (i < numForks) {
            if (!forksTaken[i] && i != id) {
                forksTaken[i] = 1;
                Zem_post(&forksTakenMutex);
                Zem_wait(&forks[i]);
                break;
            }
            i++;
            if (i == numForks) i = 0;
        }

        printf("Phil %d Eating\n", id);
        sleep(2);

        Zem_wait(&forksTakenMutex);
        forksTaken[id] = 0;
        Zem_post(&forksTakenMutex);
        Zem_post(&forks[id]);

        sleep(1);
        Zem_wait(&forksTakenMutex);
        forksTaken[i] = 0;
        Zem_post(&forksTakenMutex);
        Zem_post(&forks[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        numForks = atoi(argv[1]);
    }

    Zem_init(&forksTakenMutex, 1);
    for (int i = 0; i < numForks; ++i) {
        Zem_init(&forks[i], 1);
    }
    printf("Philosphers: begin\n");
    for (int i = 0; i < numForks - 1; ++i) {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, philospher, (void *)me);
    }
    pthread_t c;
    Pthread_create(&c, NULL, roguePhilospher, (void*)(numForks - 1));

    while (1);

    return 0;
}

