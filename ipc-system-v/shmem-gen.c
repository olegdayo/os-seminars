// shmem-gen.c
// write a random number between 0 and 999 to the shm every 1 second
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <error.h>

int main(){
  int shm_id;
  int *share;
  int num;
  key_t key = ftok(".", 0);

  srand(time(NULL));
  shm_id = shmget (key, getpagesize(), 0666 | IPC_CREAT);
  printf("shm_id = %d\n", shm_id);
  if(shm_id < 0){
    perror("shmget()");
    exit(1);
  }

  /* подключение сегмента к адресному пространству процесса */
  share = (int *)shmat(shm_id, 0, 0);
  if(share == NULL){
    perror("shmat()");
    exit(2);
  }
  printf("share = %p\n", share);

  while(1){
    num = random() % 1000;
    *share = num;
    printf("write a random number %d\n", num);
    sleep(1);
  }
  return 0;
}
