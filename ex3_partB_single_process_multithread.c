/*
 * EX NO 3 - Part B: Single Process Multithreading (SPMT)
 * Uber-like ride booking: one process creating 4 driver threads.
 * Compile: gcc ex3_partB_single_process_multithread.c -o partB -pthread
 * Run    : ./partB
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* driver(void* id) {
    long d = (long)id;
    printf("Driver %ld: Ride accepted\n", d);
    sleep(1);
    printf("Driver %ld: Ride completed\n", d);
    sleep(1);
    printf("Driver %ld: Payment received\n", d);
    return NULL;
}

int main() {
    pthread_t t[4];
    printf("Single Process: Creating 4 threads...\n");
    for (long i = 0; i < 4; i++)
        pthread_create(&t[i], NULL, driver, (void*)i);
    printf("Single Process: Waiting for all threads...\n");
    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);
    printf("Single Process: All threads finished. Program ending.\n");
    return 0;
}
