/**
 * Machine Problem 1
 * CS 241 - Spring 2016
 */

#include "vector.h"
#include "stdio.h"

// Test your vector here
int main() { 
	Vector* tester = Vector_create();
	Vector_append(tester, "A");
	Vector_append(tester, "B");
	Vector_append(tester, "C");
	//ector_append(tester, "D");
	//Vector_append(tester, "E");
	//Vector_append(tester, "F");
	Vector_insert(tester, 3, "Instead of B");
	Vector_insert(tester, 10, "NULL pointer");
	Vector_set(tester, 4, "Set Works");
	for(size_t i = 0; i < tester->size; i++)
		printf("%s\n", tester->array[i]);
	printf("%s\n", tester->array[10]);
	Vector_destroy(tester);
	return 0; 
}
