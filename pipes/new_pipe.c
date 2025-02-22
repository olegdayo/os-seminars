#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int child2parent[2];
    int parent2child[2];

    int status = pipe(child2parent);
    if (status != 0) {
        printf("Error: %s", strerror(errno));
        return 1;
    }

    status = pipe(parent2child);
    if (status != 0) {
        printf("Error: %s", strerror(errno));
        return 1;
    }

    printf("Child2parent fd: %d, %d\n", child2parent[0], child2parent[1]);
    printf("Parent2child fd: %d, %d\n", parent2child[0], parent2child[1]);

    int chpid = fork();

    if (chpid == 0) {
        char* message = "hello from child\n";
        int wrote_bytes = write(child2parent[1], message, strlen(message));
        if (wrote_bytes != strlen(message)) {
            printf("Write went wrong: %s\n", strerror(errno));
            return 1;
        }
        close(child2parent[1]);

        char buff[SIZE];
        int read_bytes = read(parent2child[0], buff, SIZE);
        if (read_bytes < 0) {
            printf("Read went wrong: %s\n", strerror(errno));
            return 1;
        }
        buff[read_bytes] = '\0';
        printf("%s", buff);
        close(parent2child[0]);
    } else {
        char* message = "hello from parent\n";
        int wrote_bytes = write(parent2child[1], message, strlen(message));
        if (wrote_bytes != strlen(message)) {
            printf("Write went wrong: %s\n", strerror(errno));
            return 1;
        }
        close(parent2child[1]);
        wait(NULL);

        char buff[SIZE];
        int read_bytes = read(child2parent[0], buff, SIZE);
        if (read_bytes < 0) {
            printf("Read went wrong: %s\n", strerror(errno));
            return 1;
        }
        buff[read_bytes] = '\0';
        printf("%s", buff);
        close(child2parent[0]);
    }

    return 0;
}
