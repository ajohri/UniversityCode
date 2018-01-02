/**
 * Mangled Mutexes Lab
 * CS 241 - Spring 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

/* You should create a struct that will get passed in by reference to your
 * start_routine. */
// typedef struct {
//   size_t start;
//   size_t end;
//   range * next;
// } range;
// Globals
size_t number_of_primes; // global number of primes you need to update
/* You should create a mutex for said global variable. */
//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
/* You should create a start routine for your threads. */

size_t isprime(size_t num) {
  size_t i;

  if(num == 1)                                          // Handling the case that 1 is a not a prime number.
    return 0;
  if(num == 2)                                          // Handling the case that 2 is a prime number.
    return 1;
  if(num == 3)                                          // Handling the case that 3 is a prime number.
    return 1;
  
  for (i = 2; i < num; i++) {                           // Diving each of these numbers by our incrementor 
    if(!(num % i))
      return 0;
  }
  return 1;
}

void incrementer(size_t start, size_t end) {            // This will increment the number that we are checking to see if it's prime.
  size_t i;
  for (i = start; i <= end; i++) {
    size_t prime_or_not = isprime(i);                   // This variable will either have 1 or 0 depending on if a number is prime.
    number_of_primes += prime_or_not;
  }
}

// size_t calculate_difference(size_t * input) {
//   size_t difference = input[1] - input[0] + 1;          // This gives us the range
//   size_t quotient = difference / input[2];              // This will give us the number of processes we need for each thread.
//   size_t mod = difference % input[2];

//   if(mod) {                                             // There is a remainder.
//     if(quotient % mod) {
      
//     }
//   }
//   else {

//   }

// }

// This function parses the arguments in argv.
// An error message is printed if any of the following happens:
//  An incorrect number of arguments are passed in.
//  'start', 'end', or 'num_threads' is less than 1.
//  'end' < 'start'.
// Else an array of 3 size_t elements are returned
// in the following order: 'start', 'end', 'num_threads'.
// It is the callers job to free the memory used.
size_t *arg_parse(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s [start] [end] [num_threads]\n", argv[0]);
    exit(1);
  }

  char *endptr;
  long tokargs[3];
  for (size_t i = 0; i < sizeof(tokargs) / sizeof(tokargs[0]); i++) {
    tokargs[i] = strtol(argv[i + 1], &endptr, 10);
    if (*endptr != '\0') {
      fprintf(stderr, "Failed to convert an arugment to a long!\n");
      exit(2);
    }
    if (tokargs[i] < 1) {
      fprintf(stderr,
              "Please have all arguments be greater than or equal to 1!\n");
      exit(3);
    }
  }
  if (tokargs[1] < tokargs[0]) {
    fprintf(stderr, "Please give a valid range!\n");
    exit(4);
  }
  size_t *args = malloc(3 * sizeof(size_t));
  for (size_t i = 0; i < sizeof(tokargs) / sizeof(tokargs[0]); i++) {
    args[i] = (size_t)tokargs[i];
  }
  return args;
}

// Call on this function when you are ready to print the result.
void print_result(size_t number_of_primes, size_t start, size_t end) {
  printf("There are %zu primes between %zu and %zu inclusive\n",
         number_of_primes, start, end);
}

// Prints the number of primes
// inbetween argv[1] and argv[2] inclusive with argv[3] threads.
int main(int argc, char *argv[]) {
  /* Your implementation goes here */
  size_t *input;
  input = arg_parse(argc, argv);                                    // Getting the input via the parser that is given to su
  incrementer(input[0], input[1]);                                  // Sending the start and end values of the range that the user gives us.
  
  print_result(number_of_primes, input[0], input[1]);               // Print statement givein to us.
  return 0;
}