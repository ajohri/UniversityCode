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
	struct node *next;
};

typedef struct node Node_T;



char **camel_caser(const char *input_str) {
   char * duplicate_input_str;
   const char s[2] = " ";
   char *token;
   Node_T *head, *curr, *prev;
   head = NULL;
   curr = NULL;
   prev = NULL;

   //newStr_flag = 1;
   duplicate_input_str = strdup(input_str);

   /* get the first token */
   token = strtok(duplicate_input_str, s);

   /* walk through other tokens */
   while( token != NULL )               // Tokenize the string
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

   curr = head;
   int j;
   int newStr_flag = 1;
   int arr_size, max_sz;
   int arr_num = 1;
   char **outpu_s;
   
   while (curr) {
      
      j = 0;
      
      while(j < curr->size) {
         if(isalpha(curr->token[j])) {
            curr -> token[j] = tolower(curr->token[j]);
         }
         if(j == 0) {
            if(!newStr_flag) {
               if(isalpha(curr->token[j])) {
                  curr->token[j] = toupper(curr->token[j]);
               }
            }
         }
         newStr_flag = 0;
         j++;
      } // end of while(j<curr -> size)
      printf ("%s\n", curr->token);
      
      //printf("%d\n", curr->size);
      
      arr_size += curr->size;
      if(ispunct(curr->token[j - 1]))
      {
         newStr_flag = 1;
         curr->contains_punct = 1;
         arr_num++;
         curr->size = arr_size;
         if(max_sz < arr_size + 1)
            max_sz = arr_size + 1;
         arr_size = 0;
      }
      curr = curr->next;
      //printf("%d\n", arr_num);
   }


   char **output_s;

   output_s = (char **)calloc(arr_num+1, sizeof(char *)); // Allocate array of pointers

   for (j = 0; j<arr_num; j++)          // Allocate  pointers
        *(output_s +j)  = (char *) calloc (max_sz+1, sizeof(char ));

   char *ptr;
   int k;

   curr = head;
   k = 0;
   ptr = *(output_s +k);

   while (curr) {                       // Copy Tokens in character arrays
//      printf ("%s\n", curr->token);
        for (j=0; j< curr->size; j++) {
                if(!ispunct(curr->token[j])){
                        *ptr = curr->token[j];
                        ptr++;
                }else {
                        *ptr = '\0';
                        k++;
                        ptr = *(output_s +k);
                }
        }
        curr = curr->next;
   }

   for (j=0;j< arr_num; j++) {
        ptr = *(output_s + j);
        printf ("%s\n", ptr);
   } 

   char **output_s;
   output_s = (char **)calloc(arr_num+1, sizeof(char *)); // Allocate array of pointers

   for (j = 0; j<arr_num; j++) {          // Allocate  pointers
        *(output_s +j)  = (char *)calloc(max_sz+1, sizeof(char ));
        //printf("%d\n", max_sz);
    }

   curr = head;

   int a;            // This is the array counter
   int k;            // This is the array's counter
   a = 0;
   k = 0;
   while(curr) {
      j = 0;
         if(curr->contains_punct){ // If the code comes across a word that has a punctuation 
            //printf("%d\n", curr->contains_punct);
            while(j < curr -> size - 1) {
               (*(output_s + a)[k]) = curr->token[j];
               j++;
               k++;
            }
            printf("%d\n", a);
            k = 0;
            a++;
         }
         else {               // If the code comes across a word that does not have a punctuation
            while(j < curr -> size) {
               //strcpy((output_s + a)[j], &curr->token[j]);
               printf("%d, %d, %d\n", a,j,k);
               (*(output_s + a)[k]) = curr->token[j];
               j++;
               k++;
            }
         }
         curr = curr->next;
   }
   exit(0);
   
   return NULL;
}



