#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char** argv) {
	int chpid = fork();
	if (chpid == 0) {
                while (1) {
                        printf("Hello, World!");
                }
	} else {
		sleep(1);
		kill(chpid, SIGKILL);
	}
	return 0;
}
