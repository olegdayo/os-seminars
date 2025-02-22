#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int fd1[] = {0, 0};
    int fd2[] = {0, 0};

    int status = pipe(fd1);
    printf("Status: %d\n", status);
    printf("fd-0 %d, fd-1 %d\n", fd1[0], fd1[1]);

    status = pipe(fd1);
    printf("Status: %d\n", status);
    printf("fd-0 %d, fd-1 %d\n", fd2[0], fd2[1]);

    int chpid = fork();
    if (chpid == 0) {
        char* message = "skibidi rizz gyatt\n";
        int wrote_bytes = write(fd1[1], message, strlen(message));
        if (wrote_bytes < 0) {
            printf("Status: %s\n", strerror(errno));
        }
        close(fd1[1]);

        char buf[SIZE];
        int read_bytes = read(fd2[0], buf, SIZE);
        if (read_bytes < 0) {
            printf("Status: %s\n", strerror(errno));
        }
        buf[read_bytes] = '\0';
        printf("Child got %s\n", buf);
        close(fd2[0]);
        wait(NULL);
    } else {
        char* message = "uzbagoisya";
        int wrote_bytes = write(fd2[1], message, strlen(message));
        if (wrote_bytes < 0) {
            printf("Status: %s\n", strerror(errno));
        }
        close(fd2[1]);

        char buf[SIZE];
        int read_bytes = read(fd1[0], buf, SIZE);
        if (read_bytes < 0) {
            printf("Status: %s\n", strerror(errno));
        }
        buf[read_bytes] = '\0';
        printf("Parent got %s\n", buf);
        close(fd1[0]);
    }

    while(1);

    return 0;
}
