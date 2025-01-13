#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int change_directory() {
    printf("Changing the root directory\n");
}

int set_resourse_limits() {
    printf("Applying a c_group\n");
}

int set_namespace() {
    printf("Creating a namespace\n");
}

int run(char** argv) {
    printf("Starting the container\n");
    execv(argv[0], argv);
}

int main(int argc, char** argv) {
    if (!strcmp(argv[1], "run")) {
        run(argv + 2);
    }
    return 0;
}
