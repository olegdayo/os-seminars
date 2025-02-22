#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

int main() {
	pid_t chpid = fork();

	if (chpid < 0) {
		printf("Something went wrong\n");
	} else if (chpid == 0) {
		printf("I am child with pid %d, my parent is %d\n", getpid(), getppid());
		exit(100);
	} else {
		int status = 10;
		wait(&status);
		printf("I am parent with pid %d, my child is %d, status %d\n", getpid(), (int)chpid, WEXITSTATUS(status));
	}
	return 0;
}
