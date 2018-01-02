#include "timers.h"
#include "mp0_b.h"

void clear_cache()
{

        double *temp_array = (double *)malloc(4096*4096*sizeof(double));
	assert (temp_array != NULL);

	for(int i=0;i<(4096*4096);i++)
		temp_array[i] = rand()%1000;

	double sum = 0;

	for(int i=0;i<(4096*4096);i++)
		sum += temp_array[i];

	free(temp_array);
}


