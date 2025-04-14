#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

struct sembuf wait = {
    .sem_num = 0,
    .sem_op = -1,
    .sem_flg = 0,
};

struct sembuf post = {
    .sem_num = 0,
    .sem_op = 1,
    .sem_flg = 0,
};

void worker(int i) {
    printf("Started by worker 2, index %d\n", i);
    printf("Critical section of worker 2, index %d\n", i);
    printf("Finished by worker 2, index %d\n", i);
}

int main(int argc, char** argv) {
    int key = ftok("./w2.c", 0);
    if (key < 0) {
        printf("Error generating key: %s\n", strerror(errno));
        return -1;
    }
    printf("Key: %d\n", key);

    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid < 0) {
        printf("Error creating sema: %s\n", strerror(errno));
        return -1;
    }
    printf("SemID: %d\n", semid);

    int status = semop(semid, &wait, 1);
    printf("Status code: %d, error: %s\n", status, strerror(errno));
    for (int i = 0; i < 2; ++i) {
        worker(i);
    }

    status = semop(semid, &wait, 1);
    printf("Status code: %d, error: %s\n", status, strerror(errno));

    status = semop(semid, &post, 1);
    printf("Status code: %d, error: %s\n", status, strerror(errno));

    return 0;
}
