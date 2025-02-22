#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pid;
    int ppid;

    pid_t chpid;

    chpid = fork();

    if (chpid == 0) {
        printf("Child process %d, my parent is %d\n", getpid(), getppid());
        exit(1);
    } else {
        // 00010000
        int status = 0;
        wait(&status);
        printf("Parent process %d, my child is %d and its status is %d\n", getpid(), chpid, WEXITSTATUS(status));
    }
}
