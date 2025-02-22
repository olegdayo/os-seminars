#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int fd = open("pipe", O_RDWR, 0444);
    if (fd < 0) {
        printf("Cannot create: %s\n", strerror(errno));
        return 1;
    }

    printf("FD: %d\n", fd);

    char buff[SIZE];
    int read_bytes = read(fd, buff, SIZE);
    printf("Read bytes: %d\n", read_bytes);
    if (read_bytes < 1) {
        printf("Cannot read: %s\n", strerror(errno));
        return 1;
    }
    buff[read_bytes] = '\0';
    printf("Message: %s\n", buff);
    return 0;
}
