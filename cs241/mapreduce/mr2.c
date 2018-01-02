/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common.h"

void usage() {
  printf("./mr2 input_file output_file mapper_exec reducer_exec num_mappers num_reducers\n");
}

int main(int argc, char **argv) {
  pid_t pid /*reducer_pid = 0*/;
  pid_t *splitter_pids;
  pid_t *mapper_pids, *reducer_pids, shuffler_pid;

  int pfd[2], input, output; 
  int **pipes, i, number_pipes, number_reducers, *fd;
  char **file_name;
  FILE * outfile;
  char curr_num[1];

  if(argc < 7)
    usage();

  number_pipes = atoi(argv[5]);   // Number of mappers
  number_reducers = atoi(argv[6]);  // Number of reducers

  splitter_pids = (pid_t *)calloc(number_pipes, sizeof(pid_t));
  mapper_pids = (pid_t *)calloc(number_pipes, sizeof(pid_t));
  reducer_pids = (pid_t *)calloc(number_reducers, sizeof(pid_t));

  pipes = (int **)calloc(number_pipes, sizeof(int *));
  for (i=0; i< number_pipes; i++) { // Input pipes for each mapper
    pipes[i] = (int *)calloc(2, sizeof(int));
  }

  fd = (int *)calloc(number_reducers, sizeof(int));
  file_name = (char **) calloc(number_reducers+2, sizeof(char *));

  file_name[0] = "./shuffler";
  for (i = 1; i <= number_reducers; i++) {  // Input file for each reducer
    file_name[i] = (char *)calloc(10, sizeof(char));
    strcpy(file_name[i], "./fifo_");
    sprintf(curr_num, "%d", i); 
    strcat(file_name[i], curr_num);                         // May need to change curr_num[1] to curr_num[2] because of null terminating
    unlink(file_name[i]);
    mkfifo(file_name[i], S_IRWXU);
  }

  input = open(argv[1], O_RDONLY);
  outfile = fopen(argv[2], "a+"); // Append mode for all the reducers
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
      sprintf(curr_num, "%d", i); // May need to pass the address
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
    } 
  }



  // Fork one instance of the shuffler
  // One input pipe for the shuffler
  // All the mappers to write to the single pipe
  // Reuse pfd[0] as the STDIN_FILENO for the shuffler
  // Open the mkfifo files
  // Shuffler to write to the mkfifo (filename[i]) files
  // Open file in read mode
  // Dup2 the fd to STDIN_FILENO of the reducer

  // int j;
  // for(j = 0; j <= number_reducers; j++)
  //   printf("MR2: Main: File Name: %s\n", file_name[j]);
  pid = shuffler_pid = fork();
  if(pid == 0) {
    if (close(pfd[1]) == -1) {
      printf("Error closing writing end of pipe \n");
      exit(1);
    }

    dup2(pfd[0], STDIN_FILENO);   // Map (read) pfd[0] to stdin
    descriptors_closeall();

    // filename an array of pointers to null-terminated strings (filenames)
    // and array of pointers must be terminated by a NULL pointer
    if((execvp(file_name[0], file_name)) == -1)
      exit(1);
    exit(0);
  }


  // open all the mkfifo files(filename[i]) in RDONLY Mode
  // fork for reducer will be in a for loop to start number_reducers reducers 
  // Map the fd ( in previous line) to STDIN_FILENO of the reducers
  // Map output to STDOUT_FILENO for every reducer.
  // Output file is opened in apend mode all reducers do not overwrite on
  // each other.

  for (i=0; i<number_reducers; i++){
    fd[i] = open(file_name[i + 1], O_RDONLY);
    descriptors_add(*fd);
  }

  for(i=0; i< number_reducers; i++) {
    pid = reducer_pids[i] = fork();
    if(pid == 0) {
      dup2(output, STDOUT_FILENO);  // Map out_file to stdout
      dup2(fd[i], STDIN_FILENO);    // Map (read) pfd[0] to stdin
      descriptors_closeall();
  
      if((execlp(argv[4], argv[4], NULL)) == -1)
        exit(1);
      exit(0);
    }
  }

  /*Parent process*/
  descriptors_closeall();
  for(i = 0; i < number_pipes; i++) { // Need to wait for all the mappers
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

  descriptors_closeall();
  for(i = 0; i < number_reducers; i++) { // Need to wait for all the mappers
      int status;
      waitpid(reducer_pids[i], &status, 0);
      if(WIFEXITED(status)) {
          int lower_bits;
          lower_bits = WEXITSTATUS(status);
          if(lower_bits != 0) {
              printf("my_reducer %d exited with status %d\n", i, lower_bits);
          }
      }  
  }
  descriptors_destroy();
  
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
  
  // All of my freeing
  free(splitter_pids);
  free(mapper_pids);
  free(reducer_pids);
  
  for(i = 0; i < number_pipes; i++) {
    free(pipes[i]);
  }
  
  free(pipes);
  free(fd);

  for(i = 1; i <= number_reducers; i++) {
    free(file_name[i]);
  }
  free(file_name);
}
