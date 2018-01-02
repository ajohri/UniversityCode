/**
 * Machine Problem 0
 * CS 241 - Spring 2016
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "part2-functions.h"

/**
 * (Edit this function to print out the "Illinois" lines in
 * part2-functions.c in order.)
 */
int main() {
  // This is for the first step (1)
  int value = 81;
  first_step(value);
  
  // This is for the second step (2)
  int * second = (int *)malloc(sizeof(int *));
  *second = 132;
  second_step(second);
  free(second);
  second = NULL;
  //free(second);

  // This is for double step (3)
  int ** third = (int**)malloc(sizeof(int*));
  *third = (int*)malloc(sizeof(int));
  *third[0] = 8942;
  double_step(third);
  free(*third);
  free(third);
  third = NULL;

  // This is for strange step (4)
  void* value4 = (void*)malloc(30);
  int* return_value4 = (int*)(value4+5);
  *return_value4 = 15;
  strange_step(value4);
  free(value4);
  value4 = NULL; 
  return_value4 = NULL;
  
  // This is for empty step (5)
  char value5[4];
  value5[3] = 0;
  empty_step(value5);

  // This is for two step (6)
  char* s2 = "uuuuuuuuu";
  void* s = s2;
  two_step(s, s2);


  // This is for three step (7)
  char* in1 = (char*)malloc(sizeof(char*));
  char* in2 = in1+2;
  char* in3 = in2+2;
  three_step(in1, in2, in3);
  free(in1);
  in1 = NULL;
  in2 = NULL;
  in3 = NULL;

  // This is for step step step (8)
  char* first2 = "Hello World";
  char* second2 = (char*)malloc(30);
  strcpy(second2, "Hello World");
  second2[2] = first2[1] + 8;
  char* third2 = (char*)malloc(30);
  strcpy(third2, "Hello World");
  third2[3] = second2[2] + 8;
  step_step_step(first2, second2, third2);
  free(second2); free(third2);
  first2 = NULL; second2 = NULL; third2 = NULL;
  

  // This is for it may be odd (9)
  char* a = (char*)malloc(sizeof(char));
  *a = 'a';
  int b = 'a';
  it_may_be_odd(a, b);
  free(a);
  a = NULL;
  

  // This is for tok step
  char* a2  = (char*)malloc(10);
  strcpy(a2, "Hi,CS241");
  tok_step(a2);
  free(a2);
  a2 = NULL;

  // This is for the end
  char* blue = (char*)malloc(10);
  blue[0] = 1;
  blue[1] = 1;
  blue[2] = 0;
  blue[3] = 1;
  void* orange = (int*)blue;
  the_end(orange, blue);
  free(blue);
  blue = NULL;
  orange = NULL;


  // your code here
  return 0;
}
