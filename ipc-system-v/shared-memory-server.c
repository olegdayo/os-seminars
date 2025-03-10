// shared-memory-server.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;             // идентификатор разделяемой памяти
  message_t *msg_p;      // адрес сообщения в разделяемой памяти
  char s[MAX_STRING];

  key_t SHM_ID = ftok(".", 0);
  // создание сегмента разделяемой памяти
  if ((shmid = shmget (SHM_ID, sizeof (message_t), PERMS | IPC_CREAT)) < 0) {
    sys_err ("server: can not create shared memory segment");
  }
  printf("Shared memory %d created\n", SHM_ID);

  // подключение сегмента к адресному пространству процесса
  if ((msg_p = (message_t *) shmat (shmid, 0, 0)) == NULL) {
    sys_err ("server: shared memory attach error");
  }
  printf("Shared memory pointer = %p\n", msg_p);

  msg_p->type = MSG_TYPE_EMPTY;
  while (1) {
    if (msg_p->type != MSG_TYPE_EMPTY) {
      // обработка сообщения
      if (msg_p->type == MSG_TYPE_STRING) {
        printf ("%s\n", msg_p->string);
      } else if (msg_p->type == MSG_TYPE_FINISH) {
        break;
      }
      msg_p->type = MSG_TYPE_EMPTY; // сообщение обработано
    }
  }

  // удаление сегмента разделяемой памяти
  shmdt (msg_p);
  if (shmctl (shmid, IPC_RMID, (struct shmid_ds *) 0) < 0) {
    sys_err ("server: shared memory remove error");
  }
  exit (0);
}

