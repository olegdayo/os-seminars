// shared-memory-client.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "message.h"

const char* shar_object = "posix-shar-object";

void sys_err (char *msg) {
  puts (msg);
  exit (1);
}

int main () {
  int shmid;            // дескриптор разделяемой памяти
  message_t *msg_p;     // адрес сообщения в разделяемой памяти
  char s[MAX_STRING];   // текст сообщения

  if ( (shmid = shm_open(shar_object, O_CREAT|O_RDWR, 0666)) == -1 ) {
    perror("shm_open");
    sys_err ("client: object is already open");
  } else {
    printf("Object is open: name = %s, id = 0x%x\n", shar_object, shmid);
  }

  //получить доступ к памяти
  msg_p = mmap(0, sizeof (message_t), PROT_WRITE|PROT_READ, MAP_SHARED, shmid, 0);
  if (msg_p == (message_t*)-1 ) {
    perror("mmap");
    sys_err ("client: incorrect memory access");
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
  //закрыть открытый объект
  close(shmid);
  return 0;
}

