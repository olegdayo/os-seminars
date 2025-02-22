#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 4

int main(int main, char** argv) {
    int curr = umask(0);
    int fd = open("tmpf", O_WRONLY, 0222);
    if (fd == -1) {
        printf("Err: %s\n", strerror(errno));
    }
    printf("Descriptor: %d\n", fd);

    char* text = "test test test\n";
    printf("Text size: %ld\n", strlen(text));

    ssize_t n = write(fd, text, strlen(text));
    printf("Total written bytes: %ld\n", n);

    int status = close(fd);
    if (status < 0) {
        printf("Failed to close fd\n");
        return -1;
    }

    fd = open("tmpf", O_RDONLY, 0444);

    printf("PID: %d\n", getpid());
    printf("Read desc: %d\n", fd);

    char buffer[SIZE];
    int i = 0;
    while (1) {
        n = read(fd, buffer, SIZE);
        buffer[n] = '\0';
        if (n == 0) {
            printf("EOF\n");
            break;
        } else if (n == -1) {
            printf("Smth went wrong\n");
            break;
        }
        printf("%d, %s\n", ++i, buffer);
    }

    status = close(fd);
    if (status < 0) {
        printf("Failed to close fd\n");
        return -1;
    }

    return 0;
}
