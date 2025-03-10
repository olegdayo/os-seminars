#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int key = ftok("ipc_w.c", 0);
    if (key < 0) {
        printf("Error generating key: %s\n", strerror(errno));
    }
    printf("Key: %d\n", key);

    int segment_id = shmget(key, SIZE, IPC_CREAT | 0666);
    if (segment_id < 0) {
        printf("Error getting segment: %s\n", strerror(errno));
    }
    printf("Segment id: %d\n", segment_id);
    
    void* segptr = shmat(segment_id, 0, SHM_W);
    printf("Pointer: %p\n", segptr);
    printf("Pointer: %ld\n", (long int) segptr);
    if ((long int) segptr < 0) {
        printf("Error getting pointer: %s\n", strerror(errno));
    }

    char* msg = "Hello, World!\n";
    strcpy(segptr, msg);
    printf("Status writing: %s\n", strerror(errno));

    return 0;
}
