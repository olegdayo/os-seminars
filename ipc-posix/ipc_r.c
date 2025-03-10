#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SIZE 4096

int main(int argc, char** argv) {
    const char* object_name = "lol";
    int fd = shm_open(object_name, O_CREAT | O_RDONLY, 0666);
    if (fd < 0) {
        printf("Failed to create file: %s\n", strerror(errno));
        return -1;
    }

    char* addr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("Shared: %s\n", addr);

    return 0;
}
