#include "list.h"
#include <thread>
#include <mutex>
#include <cstdlib>

std::mutex node_lock;

bool insert_node_lock(list *&l,int tid){
	if(is_full_lock(l)) return false;

	node_lock.lock();

	if(is_empty_lock(l)){
		node* Insert = new node();
		Insert->value = tid;
		Insert->next = Insert;
		Insert->prev = Insert;
		l->head = Insert;
	}
	else{
		node* Insert = new node;
		Insert->value = tid;
		Insert->prev = l->head->prev;
		Insert->next = l->head;
		l->head->prev = Insert;
		Insert->prev->next = Insert;
	}

	l->size ++;
	std::cout <<"the size of the list is "<<l->size<<std::endl;
	node_lock.unlock();

	return true;
}


bool delete_node_lock(list *&l,int tid)
{
	if(is_empty_lock(l)) return false;

	node_lock.lock();

	if(l->size == 1){
		delete l->head;
		l->head = NULL;
	}
	else{
		node* tail = l->head->prev;
		tail->prev->next = tail->next;
		tail->next->prev = tail->prev;
		delete tail;
	}
	
	l->size --;
	std::cout <<"the size of the list is "<<l->size<<std::endl;	
	node_lock.unlock();

	return true;

}
