#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
        pid_t pid;
        int i;
        pid_t child_pids[2];
        int status;
        pid_t rc_pid;

        for (i=0; i<2; i++){

                child_pids[i] = fork();
                pid = child_pids[i];
                /* Multiple child forking */
                switch(pid){
                        case -1:
                                /* something went wrong */
                                /* parent exits */
                                perror("fork");
                                exit(1);

                        case 0:
                                /*Children process*/
                                //child_pids[i] = getpid();
                                printf(" CHILD: number (and return value): %d PID: %d PPID: %d \n", i, getpid(), getppid());
                                exit(i);
                                break;

                                /*Missing code for parent process*/
                }
        }
        /*Parent process*/
        if (pid!=0 && pid!=-1) {
                printf("PARENT: my PID is %d\n", getpid());

                for (i=0; i<2; i++){
                        rc_pid = waitpid(child_pids[i], &status, 0);
                        if(WIFEXITED(status)) {
                                WEXITSTATUS(status);
                        }
                        if(WIFSIGNALED(status)) {
                                WTERMSIG(status);
                        }
                        if(WIFSIGNALED(status)) {
                                WCOREDUMP(status);
                        }
                        if(WIFSTOPPED(status)) {
                                WSTOPSIG(status);
                        }
                        printf("PARENT: Child: %d returned value is: %d\n", i, WEXITSTATUS(status));
               }
        }
}
