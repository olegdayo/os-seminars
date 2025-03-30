#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>     
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 4096

int main(int argc, char** argv) {
    char* key = "something";
    int fd = shm_open(key, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        printf("Error while creating memory object: %s\n", strerror(errno));
        return -1;
    }
    printf("Descriptor: %d\n", fd);

    int status = ftruncate(fd, SIZE);
    if (status < 0) {
        printf("Error while allocating: %s\n", strerror(errno));
        return -1;
    }

    void* addr = mmap(0, SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    printf("Address: %p\n", addr);

    char* message = "Hello, World!\n";
    strcpy(addr, message);

    printf("Got: %s\n", (char*) addr);

    struct stat* stats = malloc(sizeof(struct stat));
    status = fstat(fd, stats);
    if (status < 0) {
        printf("Error while getting stats: %s\n", strerror(errno));
        return -1;
    }

    printf("Blocks: %d\n", stats->st_blocks);

    status = shm_unlink(key);
    if (status < 0) {
        printf("Error while allocating: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}
