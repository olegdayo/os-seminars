#include <sys/mman.h>
#include <sys/stat.h>     
#include <fcntl.h>     
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char** argv) {
    char* key = "something";
    int fd = shm_open(key, O_CREAT | O_RDONLY, 0666);
    if (fd < 0) {
        printf("Error while creating memory object: %s\n", strerror(errno));
        return -1;
    }
    printf("Descriptor: %d\n", fd);

    void* addr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("Address: %p\n", addr);
    printf("Got: %s\n", (char*) addr);

    return 0;
}
