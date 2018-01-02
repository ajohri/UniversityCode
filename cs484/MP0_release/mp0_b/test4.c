#include "timers.h"
#include "mp0_b.h"

void test4()
{
	int *A = (int *)malloc(1024*1024*sizeof(int));
	int *B = (int *)malloc(1024*1024*sizeof(int));
	assert (A != NULL);
	assert (B != NULL);

	double total_time = 0;

	
	for(int i=0;i<1024;i++)
	for(int j=0;j<1024;j++)
		A[i*1024+j] = rand()%1000;

	for(int t=0;t<10;t++)
	{
		clear_cache();

		double t1 = get_clock();

		for(int i=0;i<1024;i++)
			for(int j=0;j<1024;j++)
				B[j*1024+i] = A[i*1024+j];

		double t2 = get_clock();

		total_time += (t2-t1);
	}

	double time_taken = total_time/10;

	free(A);
	free(B);
	
	printf("time taken for test4 = %7.16f\n",time_taken);
}


