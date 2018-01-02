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
  printf("./mr1 input_file output_file mapper_exec reducer_exec num_mappers\n");
}

int main(int argc, char **argv) {
  pid_t pid, reducer_pid;
  pid_t *splitter_pids;
  pid_t *mapper_pids;

  int pfd[2], input, output; 
  int **pipes, i, number_pipes;
  FILE * outfile;
  char curr_num[1];

  if(argc < 6)
    usage();

  number_pipes = atoi(argv[5]);

  splitter_pids = (pid_t *)calloc(number_pipes, sizeof(pid_t));
  mapper_pids = (pid_t *)calloc(number_pipes, sizeof(pid_t));
  pipes = (int **)calloc(number_pipes, sizeof(int *));
  for (i=0; i< number_pipes; i++) {     // Input pipes for each mapper
    pipes[i] = (int *)calloc(2, sizeof(int));
  }

  input = open(argv[1], O_RDONLY);
  outfile = fopen(argv[2], "w+");
  output = fileno(outfile);


  if (pipe(pfd) == -1)
  {
      printf("Error opening pipe !\n");
      exit(1);
  }

  for (i=0; i<number_pipes; i++) {
    if(pipe(pipes[i]) == -1) {
      printf("Error opening pipes for the pipes !\n");
      exit(1);
    }
    descriptors_add(pipes[i][0]);
    descriptors_add(pipes[i][1]);
  }

  descriptors_add(input);
  descriptors_add(output);
  descriptors_add(pfd[0]);
  descriptors_add(pfd[1]);

  for(i = 0; i < number_pipes; i++) {
    pid = splitter_pids[i] = fork();
    if(pid == 0) {
      dup2(pipes[i][1], STDOUT_FILENO);
      sprintf(curr_num, "%d", i);                                           // May need to pass the address
      descriptors_closeall();
      execlp("./splitter", "./splitter", argv[1], argv[5], curr_num, NULL);
      exit(0);
    } else {

    }
  }

  for(i = 0; i < number_pipes; i++) {
    pid = mapper_pids[i] = fork();
    if(pid == 0) {
      dup2(pipes[i][0], STDIN_FILENO);
      dup2(pfd[1], STDOUT_FILENO);
      descriptors_closeall();
      if((execlp(argv[3], argv[3], NULL)) == -1)
        exit(1);
      exit(0);
    } else {

    }
  }

  pid = reducer_pid = fork();
  if(pid == 0) {
    if (close(pfd[1]) == -1) {
      printf("Error closing writing end of pipe \n");
      exit(1);
    }

    dup2(output, STDOUT_FILENO); // Map out_file to stdout
    dup2(pfd[0], STDIN_FILENO); // Map (read) pfd[0] to stdin
    descriptors_closeall();

    if((execlp(argv[4], argv[4], NULL)) == -1)
      exit(1);
    exit(0);
  }

  /*Parent process*/
  descriptors_closeall();
  descriptors_destroy();
  for(i = 0; i < number_pipes; i++) {                                     // Need to wait for all the mappers
      int status;
      waitpid(mapper_pids[i], &status, 0);
      if(WIFEXITED(status)) {
          int lower_bits;
          lower_bits = WEXITSTATUS(status);
          if(lower_bits != 0) {
              printf("my_mapper %d exited with status %d\n", i, lower_bits);
          }
      }  
  }

  int nstatus;                                                             // Need to wait for the reducer.
  waitpid(reducer_pid, &nstatus, 0);

  FILE * final_output;
  char line[512];
  int counter;
  int ch;

  final_output = fopen(argv[2], "r");
  counter = 0;
  ch = 0;

  while(fgets(line, 512, final_output)) {
      counter++;
  }

  fclose(final_output);
  printf("output pairs in %s: %d\n", argv[2], counter);
}