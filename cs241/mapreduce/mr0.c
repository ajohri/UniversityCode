/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "common.h"

void usage() {
  printf("./mr0 input_file output_file mapper_exec reducer_exec\n");
}

int main(int argc, char **argv) {
  // Open the input file.

  // Create a pipe to connect the mapper to the reducer.

  // Open the output file.

  // Start the mapper.

  // Start the reducer.

  // Wait for the reducer to finish.

  // Print nonzero subprocess exit codes.

  // Count the number of lines in the output file.
  pid_t pid, rc_pid;
  pid_t child_pids[2];

  int pfd[2], input, output, i, status;


  if(argc < 5)
    usage();

  // open input and output files

  input = open(argv[1], O_RDONLY);
  output = open(argv[2], O_RDWR | O_CREAT);


  if (pipe(pfd) == -1)
  {
      printf("Error opening pipe !\n");
      exit(1);
  }

  descriptors_add(input);
  descriptors_add(output);
  descriptors_add(pfd[0]);
  descriptors_add(pfd[1]);

  for (i=0; i<2; i++){

      /* Multiple child forking */
    pid = child_pids[i] = fork();

    switch(pid) {
      case -1:
        /* something went wrong */
        /* parent exits */
        perror("fork");
        exit(1);

      case 0:
              /*Children process*/
              //child_pids[i] = getpid();
        if (i==0) {   // Mapper
          if (close(pfd[0]) == -1) {
              printf("Error closing reading end of pipe \n");
              exit(i);
          }      
          dup2(input, 0); // Map input_file to stdin
          dup2(pfd[1], 1);// Map (write) pfd[1] to stdout
          descriptors_closeall();
        } else {    // Reducer
          if (close(pfd[1]) == -1) {
            printf("Error closing writing end of pipe \n");
            exit(i);
          }
          dup2(output,1); // Map out_file to stdout
          dup2(pfd[0],0); // Map (read) pfd[0] to stdin
          descriptors_closeall();
        }
        printf(" CHILD: number (and return value): %d PID: %d PPID: %d \n", i, getpid(), getppid());
        if(i==0) {
          execl(argv[3], argv[3], NULL);
          //execvp(argv[3], argv + 3);
        } else {
          execl(argv[4], argv[4], NULL);
          //execvp(argv[4], argv + 4);
        }
        exit(i);
        break;

      default:
        break;
            /*Missing code for parent process*/
    }
  }   

  /*Parent process*/
  descriptors_closeall();
  if (pid!=0 && pid!=-1) {
      printf("PARENT: my PID is %d\n", getpid());

      descriptors_closeall();
      for (i=0; i<2; i++){
        rc_pid = waitpid(child_pids[i], &status, 0);
        printf("PARENT: Child: %d returned value is: %d\n", child_pids[i], WEXITSTATUS(status));
      }
      descriptors_destroy();
  }
}