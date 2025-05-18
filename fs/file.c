#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv) {
    int status;
    status = creat("file", 0777);
    printf("File status: %s\n", strerror(errno));

    status = symlink("file", "symlinkfile");
    printf("File status: %s\n", strerror(errno));

    status = symlink("symlinkfile", "symsymlinkfile");
    printf("File status: %s\n", strerror(errno));

    status = symlink("symsymlinkfile", "symsymsymlinkfile");
    printf("File status: %s\n", strerror(errno));

    return 0;
}
