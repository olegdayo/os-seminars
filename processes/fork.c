#include <unistd.h>
#include <stdio.h>

int main(){
	pid_t pid, ppid, chpid;
	int a = 0;
	chpid = fork();
	++a;
	pid = getpid();
	ppid = getppid();
	printf("My pid = %d, my ppid = %d, child pid = %d, result = %d\n", (int)pid, (int)ppid, (int)chpid, a);
	return 0;
} 
