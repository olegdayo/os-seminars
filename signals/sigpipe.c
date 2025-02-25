#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

void handler(int signum) {
    printf("Got SIGPIPE!\n");
}

int main(int argc, char** argv) {
    signal(SIGPIPE, handler);

    int fd[2] = {0, 0};
    int status = pipe(fd);
    if (status < 0) {
        printf("Error while creating pipe: %s\n", strerror(errno));
    }

    status = close(fd[0]);
    if (status < 0) {
        printf("Error while creating pipe: %s\n", strerror(errno));
    }

    char* message = "just a message\n";
    int wrote_bytes = write(fd[1], message, strlen(message));
    if (wrote_bytes < 1) {
        printf("Error while writing: %s\n", strerror(errno));
    }

    return 0;
}
