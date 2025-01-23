#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

// Hide node's filesystem.
int change_directory() {
    printf("Changing the root directory\n");
    mkdir("/tmp/container", 0777);
    int a = chroot("/tmp/container-fs"); // TODO: WTF???
    if (a == -1) {
        printf("%s", strerror(errno));
    }
    printf("%d\n", a);
    chdir("/");
}

// Hide node's processes.
int set_namespace() {
    printf("Creating a namespace\n");
}

// Limit resources aquired from the node.
int set_resourse_limits() {
    printf("Applying a c_group\n");
}

// Change host
int update_networking() {
    printf("Setting up networking\n");
}

// Execute the commands.
int run(char** argv) {
    printf("Starting the container\n");
    execv(argv[0], argv);
    printf("Killing the container\n");
}

int main(int argc, char** argv) {
    change_directory();
    set_namespace();
    update_networking();
    set_resourse_limits();
    if (!strcmp(argv[1], "run")) {
        run(argv + 2);
    }
    return 0;
}
