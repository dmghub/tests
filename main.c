#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <sys/resource.h>

int main(int argc, char **argv) {

    struct rlimit rl;
    pid_t pid;
    
    umask(0);
    
    int a = 10;
    
    
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
	printf("Cant't get num of limits for files\n");
    
    if ((pid = fork()) < 0) {
	printf("Error fork() execution\n");
	exit(1);
    } else if (pid == 0) {
	/* in child */
	int i;
	int fd0, fd1, fd2;
	
	printf("My new PID: %d\n", getpid());

	if (rl.rlim_max == RLIM_INFINITY)
	    rl.rlim_max = 1024;

	for (i = 0; i < rl.rlim_max; ++i)
		close(i);
	
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	
	
	openlog(NULL, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd2 != 1 || fd2 != 2)
	    syslog(LOG_ERR, "Error file descriptors %d %d %d", fd0, fd1, fd2);
	
	syslog(LOG_ERR, "Error file descriptors %d %d %d", fd0, fd1, fd2);

	unsigned int counter = 0;
	while (1) {
	    counter++;
	    sleep(1);
	}

    } else {
	/* parent */
	printf("Parent is died\n");
	exit(0);
    }

    printf("Test\n");

    return 0;
}