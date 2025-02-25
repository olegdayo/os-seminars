#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum) {
    if (signum == SIGINT) {
        printf("Hello from handler, got SIGINT\n");
    } else if (signum == SIGTERM) {
        printf("Hello from handler, got SIGTERM\n");
    } else {
        printf("Hello from handler, got something\n");
    }
}

int main(int argc, char** argv) {
    printf("%d\n", getpid());
    signal(SIGTERM, handler);
    signal(SIGINT, handler);
    while(1);
    return 0;
}
