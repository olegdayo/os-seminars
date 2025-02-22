#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char** argv) {
    umask(0);
    mknod("pipe", S_IFIFO | 0666, 0);
    int fd = open("pipe", O_RDWR, 0222);
    if (fd < 0) {
        printf("Cannot create: %s\n", strerror(errno));
        return 1;
    }

    printf("FD: %d\n", fd);

    char* msg = "hello\n";
    int wrote_bytes = write(fd, msg, strlen(msg));
    printf("Wrote bytes: %d\n", wrote_bytes);
    if (wrote_bytes < 1) {
        printf("Cannot write: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}
