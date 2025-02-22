#include <stdio.h>
#include <unistd.h>

int main() {
    printf("My id is %d, my parent id is %d\n", getpid(), getppid());
}
