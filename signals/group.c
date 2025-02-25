#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    printf("My pid is %d group is %d\n", getpid(), getpgid(getpid()));
    int status = setpgid(getpid(), 0);
    printf("Status: %d\n", status);
    int chpid = fork();
    if (chpid == 0) {
        while(1) {
            printf("Child pid is %d group is %d\n", getpid(), getpgid(getpid()));
            sleep(5);
        }
    } else {
        while(1) {
            printf("Parent pid is %d group is %d\n", getpid(), getpgid(getpid()));
            sleep(5);
        }
    }
}
