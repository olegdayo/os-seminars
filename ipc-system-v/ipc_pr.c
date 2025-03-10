#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int segment_id = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);
    if (segment_id < 0) {
        printf("Error: %s\n", strerror(errno));
    }
    printf("Segment id: %d\n", segment_id);

    void* segptr = shmat(segment_id, 0, SHM_W);
    printf("Pointer: %p\n", segptr);
    printf("Pointer: %ld\n", (long int) segptr);
    if ((long int) segptr < 0) {
        printf("Error: %s\n", strerror(errno));
    }

    char* msg = "Hello, World!\n";
    strcpy(segptr, msg);
    printf("Error: %s\n", strerror(errno));

    return 0;
}
