/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "document.h"
#include "vector.h"


#define MAXLEN 1000

Document *Document_create() {
  Document *document = (Document *)malloc(sizeof(Document));
  document->vector = Vector_create();
  assert(document);
  return document;
}

void Document_write_to_file(Document *document, const char *filename) {
  assert(document);
  assert(filename);
  // see the comment in the header file for a description of how to do this!
  // your code here!
  size_t i;

  FILE* fildes = fopen(filename, "w");
  if(fildes == NULL) {
    printf("%s", "Error!");
    exit(1);
  }
  if(Document_size < 0) {
    printf("%s", "Error!");
    exit(1);
  }

  for(i = 0; i < Document_size(document); i++) {
    if(Document_get_line(document, i) == NULL)
      fprintf(fildes, "%s", "\n");
    else
      fprintf(fildes, "%s\n", Document_get_line(document, i));
  }
  fclose(fildes);
  
}

Document *Document_create_from_file(char *filename) {
  assert(filename);
  Document* document = Document_create();
  FILE* fildes = fopen(filename, "r");
  if(fildes == NULL)
    return document;
  size_t j = 0; 
  size_t bufsize = 10000;
  char* buffer = (char*)malloc(bufsize*sizeof(char));
  while((buffer = fgets(buffer, bufsize, fildes)) != NULL) {
    buffer[strlen(buffer)-1] = '\0';
    if(*buffer == '\n')
      Document_set_line(document, j, NULL);
    else
      Document_set_line(document, j, buffer);
    j++;
  }
  free(buffer);
  fclose(fildes);
  return document;
}

void Document_destroy(Document *document) {
  assert(document);
  Vector_destroy(document->vector);
  free(document);
}

size_t Document_size(Document *document) {
  assert(document);
  return Vector_size(document->vector);
}

void Document_set_line(Document *document, size_t index, const char *str) {
  assert(document);
  Vector_set(document->vector, index, str);
}

const char *Document_get_line(Document *document, size_t index) {
  assert(document);
  return Vector_get(document->vector, index);
}

void Document_insert_line(Document *document, size_t index, const char *str) {
  assert(document);
  Vector_insert(document->vector, index, str);
}

void Document_delete_line(Document *document, size_t index) {
  assert(document);
  Vector_delete(document->vector, index);
}