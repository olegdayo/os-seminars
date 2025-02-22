#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char* args[] = {"dasdasd", "exec.c"};
    execv("/bin/cat", args);
    return 0;
}
