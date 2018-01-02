/**
 * Parallelized Poisson Problems
 * CS 241 - Spring 2016
 */
#include "barrier.h"

// The returns are just for errors if you want to check for them.
int barrier_destroy(barrier_t *t) {
  int error = 0;

  pthread_mutex_destroy(&t->mtx);
  pthread_cond_destroy(&t->cv);

  return error;
}

int barrier_init(barrier_t *t, unsigned n) {
  	int error = 0;

    t->times_used = 0;			// # of times barrier used

	t->n_threads = n;			// Max number of threads
	t->count = 0;				// Running count of threads left/joined
    pthread_mutex_init(&t->mtx, NULL);
    pthread_cond_init(&t->cv, NULL);

	return error;
}

int barrier_wait(barrier_t *t, double error) { 
	
	pthread_mutex_lock(&t->mtx);
	t->count++; 
    if (t->count == t->n_threads) { 
		t->count = 0;
		pthread_cond_broadcast(&t->cv);
	} else {
		pthread_cond_wait(&t->cv, &t->mtx); 
	}
	pthread_mutex_unlock(&t->mtx);

	return t->error;
}