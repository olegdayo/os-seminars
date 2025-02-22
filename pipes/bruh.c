#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int fd[] = {0, 0};

    int status = pipe(fd);
    printf("Status: %d\n", status);
    printf("fd-0 %d, fd-1 %d\n", fd[0], fd[1]);

    close(fd[0]);

    printf("JOPA1\n");
    char* message = "skibidi rizz gyatt\n";
    int wrote_bytes = write(fd[1], message, strlen(message));
    printf("JOPA2\n");
    if (wrote_bytes < 0) {
        printf("Status: %s\n", strerror(errno));
    }
    printf("JOPA3\n");
    printf("Aboba: %d\n", wrote_bytes);
    close(fd[1]);

    // char buf[SIZE];
    // int read_bytes = read(fd[0], buf, SIZE);
    // if (read_bytes < 0) {
    //     printf("Status: %s\n", strerror(errno));
    // }
    // buf[read_bytes] = '\0';
    // printf("Child got %s\n", buf);


    return 0;
}
