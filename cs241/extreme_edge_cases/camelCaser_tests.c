#include "camelCaser_tests.h"

#include "camelCaser.h"
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Testing function for various implementations of camelCaser.
 *
 * @param  camelCaser   A pointer to the target camelCaser function.
 * @return              Correctness of the program (0 for wrong, 1 for correct).
 */
int test_camelCaser (char ** (* camelCaser)(const char *))
{
	char **output_s;
    char *ptr;
    int j =0, ret = 1, ret1 = 1, ret2 = 1, ret3 = 1;
    int case1 = 1, case2 = 1;

    // Default Case
    output_s= camelCaser("               The Heisenbug is an incredible     5     creature         123456. Facenovel servers get their power from its indeterminism. Code smell can be ignored with INCREDIBLE use of air freshener           . God objects are the new religion         ");
    // TODO: Return 1 if the passed in function works properly; 0 if it doesn't.

    ptr = *(output_s +j);
    ret= strcmp("theHeisenbugIsAnIncredible5Creature123456", ptr);
    j++;
    ptr = *(output_s +j);
    ret1 = strcmp("facenovelServersGetTheirPowerFromItsIndeterminism", ptr);
    j++;
    ptr = *(output_s +j);
    ret2= strcmp("codeSmellCanBeIgnoredWithIncredibleUseOfAirFreshener", ptr);
    j++;
    
    if (!(ret == 0 && ret1 == 0 && ret2 == 0 ))
     	return 0;
 	
 	// Multiple punctuation case
 	output_s = camelCaser("..!?");
 	j = 0;

 	ptr = *(output_s + j);
 	ret = strcmp("", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret2 = strcmp("", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret1 = strcmp("", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret3 = strcmp("", ptr);
 	j++;

 	if(!(ret == 0 && ret2 == 0 && ret1 == 0 && ret3 == 0))
 		return 0;
 	
 	// NULL case
 	output_s = camelCaser("");
 	j = 0;

 	if(!output_s)
 		return 0;

 	output_s = camelCaser("Hello..World.");
 	j = 0;

 	ptr = *(output_s + j);
 	ret = strcmp("hello", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret1 = strcmp("", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret2 = strcmp("world", ptr);
 	j++;

 	if(!(ret == 0 && ret1 == 0 && ret2 == 0))
 		return 0;

 	camelCaser(".Hello.");
 	j = 0;

 	ptr = *(output_s + j);
 	ret = strcmp("", ptr);
 	j++;
 	ptr = *(output_s + j);
 	ret1 = strcmp("hello", ptr);
 	j++;

 	if(!(ret == 0 && ret1 == 0))
 		return 0;

 	return 1;
}
