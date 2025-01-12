#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    system("sh");
}

int main(int argc, char** argv) {
    run(argv);
    return 0;
}
