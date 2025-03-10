#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 4096

int main(int argc, char** argv) {
    int key = ftok("ipc_w.c", 0);
    if (key < 0) {
        printf("Error generating key: %s\n", strerror(errno));
    }
    printf("Key: %d\n", key);

    int segment_id = shmget(key, SIZE, 0666);
    if (segment_id < 0) {
        printf("Error get segment id: %s\n", strerror(errno));
    }
    printf("Segment id: %d\n", segment_id);
    
    void* segptr = shmat(segment_id, 0, SHM_RDONLY);
    printf("Pointer: %p\n", segptr);
    printf("Pointer: %ld\n", (long int) segptr);
    if ((long int) segptr < 0) {
        printf("Error get segment pointer: %s\n", strerror(errno));
    }

    printf("Got str: %s\n", (char*) segptr);

    int status = shmdt(segptr);
    if (status < 0) {
        printf("Error detaching: %s\n", strerror(errno));
    }

    void* info = malloc(sizeof(struct shmid_ds));
    status = shmctl(segment_id, IPC_STAT, (struct shmid_ds *) info);
    if (status < 0) {
        printf("Error calling control: %s\n", strerror(errno));
    }
    printf("Stats: %d\n", ((struct shmid_ds *) info)->shm_lpid);
    printf("Perm: %d\n", ((struct shmid_ds *) info)->shm_perm.mode);

    return 0;
}
