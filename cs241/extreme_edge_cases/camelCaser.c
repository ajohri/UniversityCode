#define _GNU_SOURCE
#include "camelCaser.h"

#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
	char * token;
	int size;
	int contains_punct;
	struct node *next;
};

typedef struct node Node_T;


char **camel_caser(const char *input_str) {
   char * duplicate_input_str;
   const char s[2] = " ";
   char *token;
   Node_T *head, *curr, *prev;
   head= curr = prev = NULL;

   duplicate_input_str = strdup(input_str);

   /* get the first token */
   token = strtok(duplicate_input_str, s);

   while( token != NULL ) 		// Tokenize the string
   {
      //printf( " %s\n", token );
     
      curr = (Node_T *)malloc(sizeof(Node_T));
      if (!curr) {
	printf("Allocation failed\n");
	exit(0);
      }
      if (prev)
	  prev->next = curr;
      if (!head)
          head= curr;
      curr->token = token;
      curr->size = strlen(token);
      curr->contains_punct = 0;
      curr->next = NULL;

      prev = curr;

      token = strtok(NULL, s);
   }

   int j;
   int newStr_flag = 1;
   int noPunch_flag = 0;
   int arr_size = 0, max_sz = 0;
   int arr_num = 0;
   
   curr = head;
   while (curr) {			// Camelize all the tokens
	j = 0;
		
    	while(j < curr->size) {				// Camelize token
    		if(isalpha(curr->token[j])) {
    			curr->token[j] = tolower(curr->token[j]);
    		}
		if(ispunct(curr->token[j]) && j< (curr->size) -1)    // For every punct
			arr_num++;
    	 	if(j == 0) {
    			if(!newStr_flag) {
    				if(isalpha(curr->token[j])) {
    					curr->token[j] = toupper(curr->token[j]);
    				}
    			}
    		}
    		newStr_flag = 0;
    		j++;
    	} 						// end of while(j<curr -> size)

//    	printf ("%s\n", curr->token);
// 	printf("%d\n", curr->size);
    	
    	arr_size += curr->size;
    	if(ispunct(curr->token[j-1]))
    	{
    		newStr_flag = 1;
    		curr->contains_punct = 1;
    		arr_num++;
    		if(max_sz < arr_size + 1)
    			max_sz = arr_size + 1;
    		arr_size = 0;
    	}
    	if(!ispunct(curr->token[j-1]) && !curr->next)
    	{
//    		newStr_flag = 1;
//    		curr->contains_punct = 1;
                noPunch_flag = 1;
//    		arr_num++;
    		if(max_sz < arr_size + 1)
    			max_sz = arr_size + 1;
//    		arr_size = 0;
    	}
    	curr = curr->next;
   }   

   char **output_s;

   output_s = (char **)calloc(arr_num+1, sizeof(char *)); // Allocate array of pointers

   for (j = 0; j< arr_num ; j++)		// Allocate  pointers
	*(output_s +j)  = (char *) calloc (max_sz+1, sizeof(char ));
      
   char *ptr;
   int k;
   int split_token;

   curr = head;
   k = 0;
   ptr = *(output_s +k);

   while (curr && (k<arr_num)) {		// Copy Tokens in character arrays
//    	printf ("%s\n", curr->token);
	for (j=0; j< curr->size; j++) {
		if(!ispunct(curr->token[j])){
			*ptr = curr->token[j];	
			ptr++;
		}else {
			*ptr = NULL;
			k++;
   			ptr = *(output_s +k);
		}
	}
    	curr = curr->next;
   }


   for (j=0;j< arr_num; j++) {
	ptr = *(output_s + j);
   	//printf ("%s\n", ptr);
   }

   free(duplicate_input_str);
   return output_s;
}