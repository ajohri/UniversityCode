#ifndef __LIST_H_
#define __LIST_H_

#include "node.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <mutex>
#include <thread>
#include <atomic>

struct list
{
	// pointers/indices for head and tail

	node *head;
	int size;
	int size_max;
};

struct thread_param
{
	int seed;
	int num_insertions;
	int num_deletions;
};


inline void init_list(int size,list *&l)
{

	 // initialize head, tail and elements

	assert (size > 0);
	l->size = 0;
	l->head = NULL;
	l->size_max = size;
}


bool insert_front_lf(list *&,int);
bool delete_back_lf(list *&,int);

inline bool is_empty_lf(list *&l)
{
	bool empty_state = false;
	if(l->size == 0){empty_state = true;}
	return empty_state;
}

inline bool is_full_lf(list *&l)
{
	bool full_state = false;
	if(l->size >= l->size_max){full_state = true;}
	return full_state;
}

void driver(list *l,thread_param&);

#endif
