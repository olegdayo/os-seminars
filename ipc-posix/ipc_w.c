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

    char* addr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    char* message = "Hello, World!\n";
    strcpy(addr, message);

    // status = shm_unlink("lol");
    // if (status < 0) {
    //     printf("Failed to create file: %s\n", strerror(errno));
    //     return -1;
    // }

    return 0;
}
