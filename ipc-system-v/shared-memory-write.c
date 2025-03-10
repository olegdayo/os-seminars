#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

// #define SHM_ID      0x1111    // ключ разделяемой памяти
#define PERMS       0666      // права доступа

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;        // идентификатор разделяемой памяти
  void *msg_p;      // адрес сообщения в разделяемой памяти
  char* message = "Hello from writer!\n";

  // Создание ключа для программ из разных каталогов
  key_t SHM_ID = ftok("~/", 0);
  // получение доступа к сегменту разделяемой памяти
  if ((shmid = shmget (SHM_ID, getpagesize(), 0)) < 0)
    sys_err ("writer: can not get shared memory segment");

  // получение адреса сегмента
  if ((msg_p = shmat (shmid, 0, 0)) == NULL) {
    sys_err ("writer: shared memory attach error");
  }

  // Пересылка сообщения в разделяемую память
  strcpy (msg_p, message);
  // Тестовое прочтение данных в разделяемой памяти
  printf("writer: shared memory using key = %x modified, id = %d\n",
         SHM_ID, shmid);
  printf("writer: message in shared memory is: %s\n", (char*)msg_p);

  return 0;
}

