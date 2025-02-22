#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int pid_to_kill = atoi(argv[1]);
	printf("I am going to kill %d\n", pid_to_kill);
	kill(pid_to_kill, SIGTERM);
}
