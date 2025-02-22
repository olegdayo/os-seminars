#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int chf() {
    return 10;
}

int pf() {
    return 20;
}

int main(int argc, char** argv) {
    pid_t chpid = 0;

    chpid = fork();

    if (chpid < 0) {
        printf("Failed to fork");
    } else if (chpid == 0) {
        int output = chf();
        printf("%d\n", output);
    } else {
        int output = pf();
        printf("%d\n", output);
        char* args[] = {"/bin/ls", "-la"};
        execv("/bin/ls", args);
    }
}
