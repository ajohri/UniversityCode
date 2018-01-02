/**
 * @file
 * Contains the implementation of the extractMessage function.
 */

#include <iostream> // might be useful for debugging
#include <assert.h>
#include "extractMessage.h"

using namespace std;

char *extractMessage(const char *message_in, int length) {
   // length must be a multiple of 8
   assert((length % 8) == 0);

   // allocate an array for the output
   char *message_out = new char[length];

	// TODO: write your code here
   for(int j = 7; j > 0; j--){					// This is telling us how many bits are going to be there
   		for(int i = 7; i > 0; i--)
   		{

   		}
   }

	return message_out;
}
