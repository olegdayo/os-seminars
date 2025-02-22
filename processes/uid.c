#include <stdio.h>
#include <unistd.h>

int main() {
    printf("User: %d, group: %d\n", getuid(), getgid());
    return 0;
}
