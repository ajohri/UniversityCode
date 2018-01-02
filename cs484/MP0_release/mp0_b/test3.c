#include "timers.h"
#include "mp0_b.h"

void test3_version1()
{
	int *A = (int *)malloc(1024*1024*sizeof(int));
	assert (A != NULL);

	for(int i=0;i<(1024*1024);i++)
		A[i] = rand()%1000;
	
	double total_time = 0;

	for(int t=0;t<10;t++)
	{
		
		clear_cache();

		double t1 = get_clock();
	
		for(int j=0;j<1024;j++)
			for(int i=0;i<1024;i++)
				A[i*1024+j]=(i+j)/2;

		double t2 = get_clock();

		total_time += (t2-t1);
	}

	double time_taken = total_time/10;
	
	free(A);

	printf("Time taken for test3 version 1 = %7.16f\n",time_taken);
}

void test3_version2()
{
	int *A = (int *)malloc(1024*1024*sizeof(int));
	assert (A != NULL);

	for(int i=0;i<(1024*1024);i++)
		A[i] = rand()%1000;

	double total_time = 0;

	for(int t = 0;t < 10; t++)
	{
		clear_cache();

		double t1 = get_clock();

		for(int i=0;i<1024;i++)
		  for(int j=0;j<1024;j++)
		  	A[i*1024+j] = (i+j)/2;

		double t2 = get_clock();

		total_time += (t2-t1);
	}	

	double time_taken = total_time/10;

	free(A);

	printf("Time taken for test3 version2 = %7.16f\n",time_taken);
}	

