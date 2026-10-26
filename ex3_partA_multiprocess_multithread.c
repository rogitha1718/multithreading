/*
 * EX NO 3 - Part A: Multiprocess Multithreading (MPMT)
 * Uber-like ride booking: 2 child processes, each running 2 driver threads.
 * Compile: gcc ex3_partA_multiprocess_multithread.c -o partA -pthread
 * Run    : ./partA
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void* driver(void* id) {
    long d = (long)id;
    printf("Driver %ld: Ride accepted\n", d);
    sleep(1);
    printf("Driver %ld: Trip done | Payment received\n", d);
    return NULL;
}

int main() {
    if (fork() == 0) {                       /* child 1: drivers 0 and 1 */
        pthread_t t[2];
        for (long i = 0; i < 2; i++)
            pthread_create(&t[i], NULL, driver, (void*)i);
        for (int i = 0; i < 2; i++)
            pthread_join(t[i], NULL);
    }
    else if (fork() == 0) {                  /* child 2: drivers 2 and 3 */
        pthread_t t[2];
        for (long i = 2; i < 4; i++)
            pthread_create(&t[i - 2], NULL, driver, (void*)i);
        for (int i = 0; i < 2; i++)
            pthread_join(t[i], NULL);
    }
    else {                                   /* parent waits for both children */
        wait(NULL);
        wait(NULL);
    }
    return 0;
}
