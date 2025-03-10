// gen-shmem.c
// write a random number between 0 and 999 to the shm every 1 second
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(){
  int shm_id;
  char gen_object[] = "gen-memory"; //  имя объекта
  int num;

  if ( (shm_id = shm_open(gen_object, O_CREAT|O_RDWR, 0666)) == -1 ) {
    perror("shm_open");
    return 1;
  } else {
    printf("Object is open: name = %s, id = 0x%x\n", gen_object, shm_id);
  }
  // Задание размера объекта памяти
  if (ftruncate(shm_id, sizeof (num)) == -1) {
    perror("ftruncate");
    return 1;
  } else {
    printf("Memory size set and = %lu\n", sizeof (num));
  }

  srand(time(NULL));
  //получить доступ к памяти
  int* addr = mmap(0, sizeof(num), PROT_WRITE|PROT_READ, MAP_SHARED, shm_id, 0);
  if (addr == (int*)-1 ) {
    printf("Error getting pointer to shared memory\n");
    return 1;
  }

  while(1){
    num = random() % 1000;
    *addr = num;
    printf("write a random number %d\n", num);
    sleep(1);
  }
  return 0;
}
