/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "common.h"

static int *descriptors_array = NULL;
static int descriptors_array_size;
static int descriptors_array_capacity;

unsigned int hashKey(char *key) {
  unsigned char *p = (unsigned char *)key;
  unsigned h = 2166136261;

  while (*p) {
    h = (h * 16777619) ^ *p++;
  }

  return h;
}

void descriptors_add(int fd) {
  if (!descriptors_array) {
    descriptors_array_capacity = 10;
    descriptors_array_size = 0;
    descriptors_array = (int *)malloc(sizeof(int) * descriptors_array_capacity);

    assert(descriptors_array);
  }

  if (descriptors_array_size == descriptors_array_capacity) {
    descriptors_array_capacity *= 2;
    descriptors_array = (int *)realloc(
        descriptors_array, sizeof(int) * descriptors_array_capacity);
  }

  descriptors_array[descriptors_array_size++] = fd;
}

void descriptors_closeall() {
  int i;
  for (i = 0; i < descriptors_array_size; i++) {
    close(descriptors_array[i]);
  }
}

void descriptors_destroy() {
  free(descriptors_array);
  descriptors_array = NULL;
}

int split_key_value(char *line, char **key, char **value) {
  char *split = strstr(line, ": ");
  char *newline = strstr(line, "\n");

  if (!split || !newline) {
    return 0; // false
  }

  *split = '\0';
  *key = line;
  *value = split + 2; // account for the extra space

  // remove the newline
  *newline = '\0';

  return 1; // true
}
