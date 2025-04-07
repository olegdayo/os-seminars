#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int cnt = 0;

void* worker(void* arg) {
    sem_t* sema = arg;

    // printf("Started\n");
    sem_wait(sema); // lock
    // Only one thread
    // sleep(1);
    // printf("Critical section\n");
    ++cnt;
    sem_post(sema); // unlock
    // printf("Finished\n");
}

int main(int argc, char** argv) {
    sem_t* sema = malloc(sizeof(sem_t));
    sem_init(sema, 0, 2);

    for (int i = 0; i < 10000; ++i) {
        pthread_t p;
        if (pthread_create(&p, NULL, worker, sema) < 0) {
            printf("Error: %s\n", strerror(errno));
        }
    }
    sleep(1);
    printf("Counted: %d\n", cnt);
    return 0;
}
