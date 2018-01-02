/**
 * Mad Mad Access Pattern
 * CS 241 - Spring 2016
 */
#include <time.h>
#include "tree.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
/*
  Look up a few nodes in the tree and print the info they contain.
  This version uses fseek() and fread() to access the data.

  ./lookup1 <data_file> <word> [<word> ...]
*/

#define MAX_LEN	80
#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

char name[MAX_LEN];
typedef struct timespec timespec_t;

int main(int argc, char **argv) { 

    char *addr, *start_addr;
    int fd;
    struct stat sb;
	uint32_t	left_child_offset, right_child_offset;
	int		i, found,residue, j;
	char		signature[4], ch;
	BinaryTreeNode	treenode;
	int		num_tokens, ret;
	timespec_t* timestart = (timespec_t*)malloc(sizeof(timespec_t));
	timespec_t* timeend = (timespec_t*)malloc(sizeof(timespec_t));

	clock_gettime(CLOCK_MONOTONIC, timestart);

	if(argc < 3) {
		printf("\n ./lookup1 <data_file> <word> [<word> ...]\n");
		free(timestart);
   		free(timeend);
		exit(1);
	}

	num_tokens = argc -2;		// Number of adwords

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        openFail(argv[1]);
        free(timestart);
   		free(timeend);
        exit(2);
    }
    
    if (fstat(fd, &sb) == -1)                  /* To obtain file size */
        handle_error("fstat");

    addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        mmapFail(argv[1]);
        free(timestart);
   		free(timeend);
        exit(2);
	}

    start_addr = addr;

    for(i = 0; i < 4; i++) {
    	signature[i] = *addr;
    	addr++;
    }

    if(strncmp(signature, "BTRE", 4) != 0) {
    	formatFail(argv[1]);
    	free(timestart);
    	free(timeend);
    	exit(2);
    }

	// Start the timer
	// Iterate thru  key words one by one
	// Search for the record corresponding to the input token
	//   - Serach based on comparing with current record
	//
	// - If record found
	//      print thte count and value
	// - Else
	//      Follow left or right offset based on the comparisong with name of
	//      current record..
	// - If we reach EOF and record not found
	//      Print the error message
	// - Pick the neck element in the adword list.
	// Find timer
	// - Print the elasped time

	i = 0;
	found = 0;

	for(j = 0; j< num_tokens; j++) { 
		while((addr - start_addr) <= sb.st_size) {
			memcpy((void *)(&treenode), (void *)addr, sizeof(BinaryTreeNode));
			addr = addr + sizeof(BinaryTreeNode);
	 		while ((ch = *addr) != '\0' ) {
	        		name[i++] = ch;
                    addr++;
	    	}
			name[i] = '\0';
			ret = strcmp(argv[2+j], name);
			if(!ret) {	// Found the match
				found = 1;
				if((i + 1) % 4 == 0)
					residue = 0;
				else
					residue = 4 - ( ( i + 1 ) % 4);					// Do calculation before in the case that i+1 % 4 is 0 then you don't need to 4-0
				addr = addr+residue;
				i=0;

				printFound(argv[2+j], treenode.count, treenode.price);
				break;
			}
			if (ret <0) {	// Go to the left child
				i=0;
				left_child_offset = treenode.left_child;
				if(left_child_offset)
					addr = start_addr+left_child_offset;
				else {
					break;
				}
			}
			if (ret > 0) {	// Go to the right child
				i=0;
				right_child_offset = treenode.right_child;
				if(right_child_offset)
					addr = start_addr+right_child_offset;
				else {
					break;
				}
			}
		}
		if(!found)
			printNotFound(argv[2+j]);
		else				// REset found for next word
			found = 0;
		addr = start_addr+4;
	}
	munmap(addr, sb.st_size);
	close(fd);
	clock_gettime(CLOCK_MONOTONIC, timeend);
	long times = ((long)(timestart->tv_sec))*1000000000 + (timestart->tv_nsec); 
   	long timee = ((long)(timeend->tv_sec))*1000000000 + (timeend->tv_nsec);
   	double duration = timee - times;
   	duration = duration/1000000000.0;
   	printTime(duration);
   	free(timestart);
   	free(timeend);
	// Find the total elapsed time
	
	return 0; 
}