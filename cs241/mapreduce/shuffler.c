/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

void usage() {
  fprintf(stderr, "shuffler destination1 destination2 ...\n");
  fprintf(stderr, "where destination1..n are files on the filesystem to which "
                  "the shuffler will write its output\n");
}

int main(int argc, char *argv[]) {
  // read from stdin
  // hash the key for the input line
  // send them to the correct output file (output files are given as command
  // line arguments
  if (argc < 2) {
    usage();
    exit(1);
  }

  char    *line = NULL;
  size_t  size = 0;
  char    *key = NULL;
  char    *value = NULL;
  unsigned int  hash;
  int   i, index, num_files;
  FILE    **fp;


  num_files = argc-1;
  fp = (FILE **)calloc(num_files, sizeof(FILE *));

  for (i=0; i < num_files; i++) {
    fp[i] = fopen(argv[i+1], "w+");
  }

  while (getline(&line, &size, stdin) != -1) {
    if (!split_key_value(line, &key, &value)) {
      fprintf(stderr, "reducer input is malformed: %s\n", line);
      exit(1);
    } else {

      // Calculate hash the key
      hash = hashKey(key);

      // Get the index corresponding to the hash
      index = hash%num_files;

      // Index used to get to the right file pointer
      fprintf(fp[index], "%s: %s\n", key, value);
    }
  }
  //printf("Shuffler: Main: Outside the while loop\n");

  for (i=0; i< num_files; i++) {
    fclose(fp[i]);
  }

  free(fp);

  return 0;
}