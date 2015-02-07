#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {


    pid_t pid;
    
    if ((pid = fork()) < 0) {
	printf("Error fork() execution\n");
	exit(1);
    } else if (pid == 0) {
	/* in child */
	printf("My new PID: %d\n", getpid());
	exit(0);
    } else {
	/* parent */
	printf("Parent is died\n");
	exit(0);
    }

    printf("Test\n");

    return 0;
}