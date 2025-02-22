// two-side-exchange.c
// Организация двустороннего обмена между родственными процессами
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define buf_size 25
char parent_message[] = "Hello, from Parent!";
int par_mes_size = sizeof(parent_message);
char child_message[] = "Hello, from Child!";
int child_mes_size = sizeof(child_message);

int main() {
  int result;
  int    fd_parent2child[2];
  int    fd_child2parent[2];
  int size;
  char   str_buf[buf_size];

  if(pipe(fd_parent2child) < 0) {
    printf("Can\'t open pipe fd_parent2child\n");
    exit(-1);
  }
  if(pipe(fd_child2parent) < 0) {
    printf("Can\'t open pipe fd_child2parent\n");
    exit(-1);
  }

  result = fork();
  if(result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  } else if (result > 0) { /* Parent process */
    // Родитель закрывает возможность чтения от потомка
    if(close(fd_parent2child[0]) < 0){
        printf("parent: Can\'t close reading side of pipe\n");
        exit(-1);
    }
    // Родитель шлет приветствие потомку
    size = write(fd_parent2child[1], parent_message, par_mes_size);
    if(size != par_mes_size){
      printf("Can\'t write all string to pipe\n");
      exit(-1);
    }
    // Родитель перекрывает канал parent->child
    if(close(fd_parent2child[1]) < 0) {
      printf("parent: Can\'t close writing side of pipe\n");
      exit(-1);
    }
    // Родитель перекрывает возможность передачи потомку
    if(close(fd_child2parent[1]) < 0){
      printf("parent: Can\'t close child writing side of pipe\n");
      exit(-1);
    }
    // Чтение информации от потомка
    size = read(fd_child2parent[0], str_buf, par_mes_size);
    if(size < 0){
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }

    printf("Parent exit, str_buf: %s\n", str_buf);
  } else { /* Child process */
    // Потомок закрывает канал записи от родителя
    if(close(fd_parent2child[1]) < 0){
      printf("child: Can\'t close writing side of pipe\n");
      exit(-1);
    }
    size = read(fd_parent2child[0], str_buf, par_mes_size);
    if(size < 0){
        printf("Can\'t read string from pipe\n");
        exit(-1);
    }

    // Потомо закрывает канал чтения от родителя
    if(close(fd_child2parent[0]) < 0){
        printf("child: Can\'t close reading side of pipe\n");
        exit(-1);
    }
    // Пересылка приветствия родителю
    size = write(fd_child2parent[1], child_message, child_mes_size);
    if(size != child_mes_size){
      printf("Can\'t write all child string to pipe\n");
      exit(-1);
    }

    // Полное закрытие канала child->parent
    if(close(fd_child2parent[1]) < 0) {
      printf("child: Can\'t close child writing side of pipe\n");
      exit(-1);
    }

    printf("Child exit, str_buf: %s\n", str_buf);
    if(close(fd_parent2child[0]) < 0){
        printf("child: Can\'t close reading side of pipe\n"); exit(-1);
    }
  }

  return 0;
}
