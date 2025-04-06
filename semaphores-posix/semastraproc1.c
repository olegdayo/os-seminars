#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SIZE 4096

void* worker(sem_t* sema, int* cnt) {
    printf("Started\n");
    sem_wait(sema);
    printf("Critical section\n");
    ++(*cnt);
    // sleep(1);
    sem_post(sema);
    printf("Finished\n");
}

int main(int argc, char** argv) {
    const char* object_name = "lol";
    int fd = shm_open(object_name, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        printf("Failed to create file: %s\n", strerror(errno));
        return -1;
    }

    int status = ftruncate(fd, SIZE);
    if (status < 0) {
        printf("Failed to truncate: %s\n", strerror(errno));
        return -1;
    }

    sem_unlink("/lol");
    sem_t* sema = sem_open("/lol", O_CREAT | O_RDWR, 0666, 1);
    if (!sema) {
        printf("Failed to create sema: %s\n", strerror(errno));
        return -1;
    }

    int* cnt = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < 1000; ++i) {
        worker(sema, cnt);
    }

    sleep(2);
    sem_wait(sema);
    printf("I: %d\n", *cnt);
    *cnt = 0;
    sem_post(sema);
}
