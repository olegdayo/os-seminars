#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* worker(void* arg) {
    sem_t* sema = arg;
    sem_wait(sema);
    printf("Entered..\n");
    sleep(1);
    printf("Exited...\n");
    sem_post(sema);
}

int main(int argc, char** argv) {
    sem_t sema;
    sem_init(&sema, 0, 4);

    for (int i = 0; i < 10; i++) {
        pthread_t p;
        pthread_create(&p, NULL, worker, &sema);
    }
    sleep(20);
    return 0;
}
