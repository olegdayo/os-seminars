#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
	printf("KEK\n");
}

int main(int argc, char** argv) {
	printf("%d\n", getpid());
	(void)signal(SIGTERM, handler);
	while (1) {
		printf("LOL\n");
		sleep(1);
	}
}

