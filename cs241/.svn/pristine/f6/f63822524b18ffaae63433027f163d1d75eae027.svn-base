/**
 * Overworked Interns Lab
 * CS 241 - Spring 2016
 */
#include "company.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Bad solution that will deadlock
void *work_interns(void *p) {
  Company *company = (Company *)p;
  pthread_mutex_t *left_intern, *right_intern;
  int flag;
  while (running) {
    left_intern = Company_get_left_intern(company);
    right_intern = Company_get_right_intern(company);
    // Every company grabs their left intern
    if(left_intern == right_intern || right_intern == NULL || left_intern == NULL)
    {
    	Company_have_board_meeting(company);
    }
    else {
	    if(left_intern < right_intern) {
	    	flag = 1;
	    	pthread_mutex_lock(left_intern);
	    }
	    else {
	    	flag = 0;
	    	pthread_mutex_lock(right_intern);
	    }

	    if(flag) {
	    	pthread_mutex_lock(right_intern);
	    }
	    else {
	    	pthread_mutex_lock(left_intern);
	    }
	    
	    Company_hire_interns(company);
	    pthread_mutex_unlock(right_intern);
	    pthread_mutex_unlock(left_intern);
	    Company_have_board_meeting(company);
	  }
	}
  return NULL;
}
