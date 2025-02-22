#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int status = access("tmpf", F_OK);
    printf("%d\n", status);
    if (status != 0) {
        if (errno == ENOENT) {
            printf("File does not exist\n");
        } else if (errno == EACCES) {
            printf("File is not accessible\n");
        }
    }
    return 0;
}
