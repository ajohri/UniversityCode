#include "list.h"
#include <thread>
#include <mutex>

extern std::atomic<int> global;

bool insert_front_lf(list *&l, int tid)
{

	int local = 1;
	// Using the lock here
	while(std::atomic_exchange(&global, local)){}

	if(is_full_lf(l)){
		local = 0;
		std::atomic_exchange(&global, local);
		return false;
	}

	// If the list is empty we will start the list here.
	if(is_empty_lf(l)) {
			node* Insert = new node();

			Insert->value = tid;
			Insert->next = Insert;
			Insert->prev = Insert;
			l->head = Insert;
	}
	// Inserting a new element here.
	else{
			node* Insert = new node;

			Insert->value = tid;
			Insert->prev = l->head->prev;
			Insert->next = l->head;
			l->head->prev = Insert;
			Insert->prev->next = Insert;
		}

		l->size ++;
	
		local = 0;
		std::atomic_exchange(&global, local);
		// Releasing the lock here
		return true;
}

bool delete_back_lf(list *&l,int tid)
{
	int local = 1;
	while(std::atomic_exchange(&global, local)){}

	if(is_empty_lf(l)){
		local = 0;
		std::atomic_exchange(&global, local);
		return false;
	}

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
		//std::cout <<"the size of the list is "<<l->size<<std::endl;

		local = 0;
		std::atomic_exchange(&global, local);
		return true;
}
