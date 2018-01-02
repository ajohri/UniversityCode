#ifndef __LIST_H_
#define __LIST_H_

#include "node.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <mutex>
#include <thread>

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

extern std::mutex node_lock;

inline void init_list(int size,list *&l)
{
	assert (size > 0);
	l->size = 0;
	l->head = NULL;
	l->size_max = size;
}

bool insert_node_lock(list*&,int); // insert at head
bool delete_node_lock(list *&,int); // delete from tail

inline bool is_empty_lock(list *&l)
{
	bool empty_state = false;
	if(l->size == 0) {
		empty_state = true;
	}
	return empty_state;
}

inline bool is_full_lock(list *&l)
{
	bool full_state = false;
	if(l->size >= l->size_max) {
		full_state = true;
	}
	return full_state;
}

void driver(list *,thread_param &);

#endif
