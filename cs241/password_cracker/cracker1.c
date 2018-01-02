/**
 * Machine Problem: Password Cracker
 * CS 241 - Spring 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "cracker1.h"
#include "thread_status.h"
#include "utils.h"
#include <unistd.h>
#include "crypt.h"
#include "format.h"

#define MAX_QUEUE 512
#define MAX_SIZE 512

Queue task_queue;
char line[MAX_SIZE];
char *buff;

int number_of_passwords_recovered = 0;
int number_of_passwords_not_recovered = 0;

// Use the logic in editor to read a line
// - Code for reading a line
// We will creat a special node to show the last line
// Creat a queue. One node for each line int password file
// Creat a thread pool
// - Each thred to pull an elemnt from the node
// - Process the elemnt
// - Thread exits when it hits the special node ( for end of file)
// Join all the threads
// - Pull the last node
// - Destroy the queue 

// Create the required number of threads and launch the same to process nodes in the
// shared queue.

char * crack_password(char * in, int prefix, int * count, const char * hash) {

	unsigned int i;
	int success = 1;
	int result = 1;

	struct crypt_data cdata;
	cdata.initialized = 0;
	
	for( i = prefix; i < strlen(in); i++) {										// Changes all the .'s to a's.
		in[i] = 'a';
	}
	
	while(success) {
		char * hashed = crypt_r(in, "xx", &cdata);								// Encrypting each permutation that we have and storing it in a variable.
		*count = *count + 1;													// Incrementing the counter everytime we do an encryption.
		if(!strcmp(hashed, hash)) {												// Comparing to see if our hashed value matches the hash that was given to us.
			success = 0;														// Setting the proper flags to notify us that we have found a match.
			result = 0;
		}
		else {
			success = incrementString(in + prefix);								// Modifying the string to get the next permuation that we need to test on line 59.
			if(success == 0) {
				hashed = crypt_r(in, "xx", &cdata);								// Checking the edge case and last permutation with the z's.
				if(!strcmp(hashed, hash)) {
					result = 0;
				}
			}
		}
	}
	if(result == 1) {
		number_of_passwords_not_recovered++;									// Keep track of how many passwords we did not recover.
		return NULL;
	}
	else {
		number_of_passwords_recovered++;										// Keep track of how many passwords we did recover.
	}

	return in;
}


// This is the function that is all the threads are calling upon.
void * process_task(void * ptr) {
	char *task, *username, *hash, *in, *ret;
	char *copy_string;
	char *token;
	char *brkt;
  	unsigned int	thread_id;
  	int prefix, count = 0;
  	int mod_counter = 0;

  	int index = (intptr_t)ptr;
  	index++;

  	Queue * queue = (Queue *)ptr;

	thread_id = pthread_self();
	while(1) {
		task = (char *)Queue_pull(queue);										// Getting each line from the queue.
	  	if(task == NULL) {
			Queue_push(queue, NULL);
			break;
		}
		else
		{
			copy_string = (char *)calloc(strlen(task) + 2, sizeof(char));		// Copy string is being intialized.
			strcpy(copy_string, task);
			token = strtok_r(copy_string, " ", &brkt);
			username = token;													// Cutting the first part of the string to get the username.
			v1_print_thread_start(index, username);
			token = strtok_r(NULL, " ", &brkt);
			hash = token;														// Cutting the second part of the string to get the hash of the correct password.
			token = strtok_r(NULL, " ", &brkt);
			in = token;															// Setting the last part of the string to the partial password that is given to us.
			prefix = getPrefixLength(in);
			mod_counter = prefix;
			while(in[mod_counter] == '.') {
				mod_counter++;
			}
			in[mod_counter] = '\0';												// Adding a null ternimating character at the end of the input string.
			ret = crack_password(in, prefix, &count, hash);
			if(ret)
				v1_print_thread_result( thread_id, username, ret, count, getThreadCPUTime(), 0);
			else
				v1_print_thread_result( thread_id, username, ret, count, getThreadCPUTime(), 1);
		}
		
	}

	return NULL;
}


int start(size_t thread_count) {
  	double startTime = getTime();												// Gets the time at which the program starts running.
  	Queue_init(&task_queue, MAX_QUEUE);

	while(fgets(line, MAX_SIZE, stdin)) {										// Gets each line from stdin
  		buff = (char *)calloc(512, sizeof(char));								// Allocating space for the buff so that we can copy the contents into this buff.
  		strcpy(buff, line);														
  		Queue_push(&task_queue, buff);											// Storing each buff value into the Queue.
  	}
  	Queue_push(&task_queue, NULL);												// Push this in for later logic. (line number 103).
  
  	pthread_t	*threads;
  	size_t i;

	threads = (pthread_t *)calloc(thread_count, sizeof(pthread_t));

  	for (i = 0; i<thread_count; i++) {											// Creating each threading and giving a specific line to do everything in.
		pthread_create(&threads[i], NULL, &process_task, (void *)(&task_queue));
  	}

  	for (i = 0; i< thread_count; i++)
		pthread_join(*(threads +i), NULL);

  	double endTime = getTime();
  	double total = endTime - startTime;
  	printf("Total CPU Time: %f\n", total);

	return 0;
}