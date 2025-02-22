#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
	printf("BOOBA\n");
}

int main(int argc, char** argv) {
	printf("%d\n", getpid());
	(void)signal(SIGTERM, handler);
	while (1) {
		printf("ABOBA\n");
		sleep(1);
	}
}

