#define _GNU_SOURCE

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "format.h"
#include <string.h>


int main(int argc, char *argv[]) {

    struct timespec ts;
    double	elapsedSeconds, startSeconds, endSeconds;
    pid_t	pid;
    int		status;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    startSeconds= (((double)ts.tv_sec * 1000000000.0) + (double)ts.tv_nsec) / 1000000000.0;
    pid = fork();

    if(argc <= 1) {
    	print_time_usage();
    }
    
    if ( pid > 0) {			// Parent

        waitpid(pid, &status, 0);
    	clock_gettime(CLOCK_MONOTONIC, &ts);
        
		endSeconds= (((double)ts.tv_sec * 1000000000.0) + (double)ts.tv_nsec) / 1000000000.0;

        elapsedSeconds = endSeconds - startSeconds;
		display_results(argv, elapsedSeconds);
		return(elapsedSeconds);

    } 
    if ( pid == 0) {		// Child
 	execvp(argv[1], &argv[1]);
	print_exec_failed();
    } else { 				// Fork failed
        print_fork_failed();
    }

    return 0;
}