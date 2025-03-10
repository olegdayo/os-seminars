// shared-memory-client.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;            // идентификатор разделяемой памяти
  message_t *msg_p;     // адрес сообщения в разделяемой памяти
  char s[MAX_STRING];   // текст сообщения

  key_t SHM_ID = ftok(".", 0);
  // получение доступа к сегменту разделяемой памяти
  if ((shmid = shmget (SHM_ID, sizeof (message_t), 0)) < 0) {
    sys_err ("client: can not get shared memory segment");
  }

  // получение адреса сегмента
  if ((msg_p = (message_t *) shmat (shmid, 0, 0)) == NULL) {
    sys_err ("client: shared memory attach error");
  }

  // Организация передачи сообщений
  while (1) {
    fgets(s, MAX_STRING, stdin);
    int len = strlen(s);
    s[len-1] = '\0';
    // int bye = strcmp(s, "bye");
    if(s[0] != '\0') {
      // Не прощаемся.
      // Записать сообщение о передаче строки
      msg_p->type = MSG_TYPE_STRING;
      strncpy (msg_p->string, s, MAX_STRING);
    } else {
      // Записать сообщение о завершении обмена
      msg_p->type = MSG_TYPE_FINISH;
    };
    if(msg_p->type == MSG_TYPE_FINISH) {
      break;
    }
  }
  // Окончание цикла передачи сообщений
  shmdt (msg_p);  // отсоединить сегмент разделяемой памяти
  exit (0);
}

