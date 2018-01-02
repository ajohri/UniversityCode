#include <stdio.h>
#include <stdlib.h>


typedef struct Block {
  struct Block *next;
  size_t size;  // # of usable bytes in this block
  int is_free; // 0 (allocated) or 1 (available)
} Block;

Block * head = NULL;
Block * prev = NULL;



void * traverse(Block * head, size_t size) {
	//printf("Traverse: Inside the function\n");
	Block * current;
	Block * worst_case;
	size_t check_size;
	
	current = head;
	worst_case = head;
	check_size = 0;
	//printf("Traverse: Before the while loop\n");
	while(current != NULL) {
		//printf("Traverse: Inside the while loop\n");
		if(current->size >= size) {
				if(current->is_free == 1){	// Flag Check. The space is free at this point.
					if(current->size > check_size) {
						current->is_free = 0;
						check_size = current->size;
						printf("Traverse: Check_Size: %zu\n", check_size);
						worst_case->is_free = 1;
						worst_case = current;
					}
				}
		}
		prev = current;
		current = current->next;		// Advancing location in the list.
	}
	if(worst_case == head && worst_case->is_free == 0)
		worst_case = NULL;
	return worst_case;
}


void * allocate(size_t size) {
	//printf("Allocate: Inside the function\n");
	Block * current;
	current = head;
	if(head == NULL) {
		//printf("Allocate: Should come here on first iteration\n");
		head = current = malloc(size + sizeof(Block));
		current->size = size;
		current->is_free = 0;
		prev = head;
		current->next = NULL;
		//printf("Allocate: After Malloc\n");
	} else {
		//printf("Allocate: Before we call traverse\n");
		current = (Block *)(traverse(head, size));
		//printf("Allocate: After we call traverse\n");
		if(current == NULL) {				// We could not find a block that had the correct size so we need to make it now.
			printf("Allocate: Coming inside the current == NULL condition\n");
			Block * temp = NULL;
			temp = malloc(size + sizeof(Block));
			temp->size = size;
			temp->is_free = 0;
			temp->next = NULL;
			prev->next = temp;
			current = temp;
		}
	}
	//printf("Allocate: Before the return statement\n");
	return ((char *)current + sizeof(Block));
}

void release(void * need_to_free) {
	Block * start_of_frame = NULL;			// Getting to the beginning of the address.
	start_of_frame = (Block *)((char *)need_to_free - sizeof(Block));
	start_of_frame->is_free = 1;											// Changing the flag
	// Need to write this still.
}

int main() {
	//printf("Main: Inside the main function\n");
	char * temp;
	Block * btemp;
	Block * current;

	temp = (char *)allocate(100);
	//printf("Main: After the first allocate\n");
	release(temp);
	//printf("Main: After the first release\n");

	//printf("Main: Before the second allocate\n");
	temp = (char *)allocate(200);
	//printf("Main: Before the second release\n");
	release(temp);

	temp = (char *)allocate(50);
	btemp = (Block *)((char *)temp - sizeof(Block));
	printf("Main: Btemp Size: %zu\n", btemp->size);

	current = head;
	while(current != NULL){
		printf("Main: Address of Node: %p\n", current);
		current = current->next;
	}


	return 0;
}