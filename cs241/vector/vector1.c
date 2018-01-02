/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

/* An automatically-expanding array of strings. */
#include "vector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

/* Allocate and return a new Vector structure. */
Vector *Vector_create() {
  // your code here
  Vector * created = NULL;
  created = (Vector *)malloc(sizeof(Vector));
  created->array = (char **)malloc(sizeof(char *));
  created->capacity = INITIAL_CAPACITY;
  created->size = 0;
  size_t i;
  for(i = 0; i < created->size; i++) {
    created->array[i] = NULL;
  }

  return created;
}

/**
 * Deallocate a Vector structure.
 * Every non-NULL entry in array from array[0] to array[size-1] will
 * need to be free()d.
*/
void Vector_destroy(Vector *vector) {
  size_t i;
  for(i = 0; i < vector->size; i++) {
    if(!vector->array[i]) {
      free(vector->array[i]);
      vector->array[i] = NULL;
    }
  }
  free(vector->array);
  assert(vector);
  // your code here
}

/* Return the number of entries in use in this array. */
size_t Vector_size(Vector *vector) {
  size_t i;
  int counter = 0;
  for(i = 0; i < vector->size; i++) {
    if(!vector->array[i])
      counter++;
  }
  assert(vector);
  // your code here
  return counter;
}

/**
 * Sets the size of the array.
 *
 * If the array grows, new entries will be initialized to NULL.
 * If the array shrinks, entries past the new end of the array
 * will be deallocated.
 *
 * If the new size is larger than the capacity of the array, the
 * capacity will need to be increased, meaning the array will need to
 * be reallocated.  The new capacity should be at least twice as big
 * as it was before. In other words:
 *
 * if new_size > capacity:
 *      new_capacity = maximum(capacity * 2, new_size);
*/
void Vector_resize(Vector *vector, size_t new_size) {
  assert(vector);
  // your code here
}

/**
 * Allocate a copy of 'str' and store it in array[index].  If 'str' is NULL,
 * just store NULL in array[index].  Note that if the vector is allocating
 * memory for the entry (which will happen when th entry is not NULL), then it
 * should also be the freeing it (hint,hint)
*/
void Vector_set(Vector *vector, size_t index, const char *str) {
  char *ptr =NULL;
  char *copy = NULL;
  assert(vector);
  if(index > vector->size)
    Vector_resize(vector, index + 1);

  ptr= vector->array[index];
  if (ptr)
    free(ptr);

  copy = strdup(str); 
  ptr = copy; // put the string here.
  // your code here
}


/**
 * Returns the entry stored at array[index].
 * If array[index]==NULL, this will return NULL.
 *
 * This does not return a copy of the entry; it returns the actual
 * char* stored at array[index]. This means the caller must not
 * deallocate the entry (if the entry is non-null).
*/
 const char *Vector_get(Vector *vector, size_t index) {
  assert(vector);
  // your code here
  char *ptr = NULL;

  ptr = vector->array[index];

  if(!ptr || index > vector->size)
    return NULL;
  return ptr; 
}

/**
 * Inserts a copy of 'str' or NULL if str is NULL
 * and stores it in array[index].
 * Note the array[index] could already contain a entry,
 * in which case the entry at array[index] and all subsequent
 * entries should be shifted down.
 * Also note that index could be well beyond the position of
 * the last entry. In which case the vector should resize()
 * to barely accommodate that new entry.
*/
void Vector_insert(Vector *vector, size_t index, const char *str) {
  assert(vector);
  char * ptr_dup = strdup(str);

  if((vector->capacity - vector->size) == 1)
  {
    Vector_resize(vector, index);
  }

  if(index > vector->size /*|| (vector->array[index] == NULL)*/) {
    vector->array[index] = ptr_dup;
    if(vector->size < index) {
      vector->size = index;
    }
  }

  // Shift Logic
  size_t curr_size = vector->size;
  for(; curr_size >= index;) {
    vector->array[curr_size - 1] = vector->array[curr_size];
    curr_size = curr_size - 1;
  }

  vector->array[index] = ptr_dup;
  vector->size += 1;

  // your code here
}

/**
 * Removes whatever entry is contained in array[index].
 * Note that index does not have to be the last element of the vector,
 * in which case you should not only remove the entry at array[index],
 * but also shift all subsequent entries down.
 * Do not forget to resize the vector accordingly.
*/
void Vector_delete(Vector *vector, size_t index) {
  assert(vector);
  // your code here, what asserts might you want?
}

/**
 * Inserts 'str' (or NULL) right after the last element in the vector.
*/
void Vector_append(Vector *vector, const char *str) {
  assert(vector);
  // your code here
}
