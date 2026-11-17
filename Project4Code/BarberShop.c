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

Zem_t barberReady;
Zem_t barberSleepy;
Zem_t occupiedChairs;
int numChairs = 4;
int waiting = 0;
int numBarbers = 2;

void *Barber(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;
    printf("Barber %d Clocks in \n", id);
    while (1) {
        if (!waiting) {
            printf("Barber %d Goes to sleep \n", id);
            Zem_wait(&barberSleepy);          // go to bed
            printf("Barber %d Wakes Up \n", id);
        }
        else {
            Zem_wait(&barberSleepy);
        }
        Zem_wait(&occupiedChairs);
        waiting--;                        // customer leaves cuase hair was cut
        Zem_post(&occupiedChairs);
        Zem_post(&barberReady);           // go to next customer
        sleep(1);
    }
}

void *Customer(void *arg) {
    long long int value = (long long int) arg;
    int id = (int) value;

    printf("Customer %d Enters Store \n", id);
    Zem_wait(&occupiedChairs);
    if (waiting == numChairs) {          // no more chairs so leave
        Zem_post(&occupiedChairs);
        printf("Customer %d Leaving\n", id);
        return NULL;
    }
    waiting++;
    Zem_post(&occupiedChairs);

    Zem_post(&barberSleepy);              // wake the barber
    Zem_wait(&barberReady);               // wait for haircut
    printf("Customer %d Got Haircut and Leaves\n", id);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        numChairs = atoi(argv[1]);
    }

    Zem_init(&barberSleepy, 0);
    Zem_init(&barberReady, 0);
    Zem_init(&occupiedChairs, 1);
    printf("Barber Shop: begin\n");

    for (int i = 0; i < numBarbers; ++i) {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, Barber, (void *)me);
    }

    for (int i = 0; i < numChairs + 3; ++i) {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, Customer, (void *)me);
    }

    while (1);

    return 0;
}

