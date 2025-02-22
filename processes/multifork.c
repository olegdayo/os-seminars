#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	char pid[255];
	int a = 0;
	int* b = &a;

	fork();
	fork();
	fork();

	++(*b);
	printf("PID: %d\n", getpid());
	printf("a: %d\n", *b);
	exit(0);
}
