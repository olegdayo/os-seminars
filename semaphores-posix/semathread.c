#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int i = 0;

void* worker(void* arg) {
    sem_t* sema = arg;
    printf("Started\n");
    sem_wait(sema);
    printf("Critical section\n");
    ++i;
    // sleep(1);
    sem_post(sema);
    printf("Finished\n");
}

int main(int argc, char** argv) {
    sem_t* sema = malloc(sizeof(sem_t));
    sem_init(sema, 0, 1000);

    for (int i = 0; i < 1000; ++i) {
        pthread_t p;
        pthread_create(&p, NULL, worker, sema);
    }
    sleep(1);
    printf("I: %d\n", i);
}
