#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 4096

int main() {
    umask(0);

    int descriptor = open("tmpf", O_WRONLY | O_CREAT, 0777);
    printf("Descriptor is %d\n", descriptor);
    printf("Error: %s\n", strerror(errno));

    char* text = "hello\n";
    printf("String length: %ld\n", strlen(text));

    int wrote_bytes = write(descriptor, text, strlen(text));
    printf("Wrote bytes: %d\n", wrote_bytes);

    int status = close(descriptor);
    printf("Status: %d\n", status);

    descriptor = open("tmpf", O_RDONLY, 0444);

    char buffer[SIZE];
    int read_bytes = read(descriptor, buffer, SIZE);
    printf("Read bytes: %d\n", read_bytes);

    buffer[read_bytes] = '\0';
    printf("Buffer: %s\n", buffer);

    status = close(descriptor);
    printf("Status: %d\n", status);
}
