/**
 * Terrible Threads Lab
 * CS 241 - Spring 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


/**
 *  Given data, place it on the queue.  Can be called by multiple threads.
 */
void queue_push( queue_t *queue,  void* data) {

	queue_node_t* node = malloc(sizeof(queue_node_t));
	node->data = data;
	node->next = NULL;
	pthread_mutex_lock(&queue->m);
	if(queue->maxSize > 0) {
		while(queue->size == queue->maxSize)
			pthread_cond_wait(&queue->cv, &queue->m);
	}
	if(queue->size == 0) {
		queue->head = node;
		queue->tail = node;
		queue->size++;
		pthread_cond_signal(&queue->cv);
		pthread_mutex_unlock(&queue->m);
		return;
	}
	queue->tail->next = node;
	queue->tail = node;
	queue->size++;
	pthread_cond_signal(&queue->cv);	
	pthread_mutex_unlock(&queue->m);
	return;
}


/**
 *  Retrieve the data from the front of the queue.  Can be called by multiple
 * threads.
 *  Blocks the queue is empty
 */
void* queue_pull(queue_t *queue) {

	pthread_mutex_lock(&queue->m);
  	while(queue->size == 0)
  		pthread_cond_wait(&queue->cv, &queue->m);
  	queue_node_t* current = queue->head;
  	void* return_value;
  	if(queue->size == 1) {
  		return_value = current->data;
  		queue->head = NULL;
  		queue->tail = NULL;
  		free(current);
  		queue->size--;
  		pthread_cond_signal(&queue->cv);
  		pthread_mutex_unlock(&queue->m);
  		return return_value;
  	}
  	
  	return_value = queue->head->data;
  	queue->head = queue->head->next;
  	free(queue->head);	
  	queue->size--;
  	pthread_cond_signal(&queue->cv);
  	pthread_mutex_unlock(&queue->m);
  	return return_value;
}


/**
 *  Initializes the queue
 */
void queue_init(queue_t *queue, int maxSize){

	queue->maxSize = maxSize;
	pthread_mutex_init(&queue->m, NULL);
	pthread_cond_init(&queue->cv, NULL);
}


/**
 *  Destroys the queue, freeing any remaining nodes in it.
 */
void queue_destroy(queue_t *queue){

	int		size;
	queue_node_t	*node;

	for(size=0; size<queue->size; size++) {
		node = queue_pull(queue);
		free(node);
	}
	
}