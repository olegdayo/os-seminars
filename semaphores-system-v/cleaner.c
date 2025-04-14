#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

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

    int status = semctl(semid, 0, IPC_RMID);
    printf("Status code: %d, error: %s\n", status, strerror(errno));
}
