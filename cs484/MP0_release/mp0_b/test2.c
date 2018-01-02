#include "timers.h"
#include "mp0_b.h"

void test2_version1()
{
	int *  A = (int *)malloc(1000000*sizeof(int));
	int *  B = (int *)malloc(1000000*sizeof(int));
	int *  C = (int *)malloc(1000000*sizeof(int));

	assert (A != NULL);
	assert (B != NULL);
	assert (C != NULL);
	
	for(int i=0;i<1000000;i++)
	{
		A[i] = rand()%100000;
		B[i] = rand()%100000;
	}

	double total_time = 0;

	for(int t=0;t<10;t++)
	{
		clear_cache();

		double t1 = get_clock();
	
		for(int i=0;i<1000000;i++)
			C[i] = A[i]+B[i];
	
		double t2 = get_clock();
	
		total_time += (t2-t1);
	}

	double time_taken = total_time/10;

	free(A);
	free(B);
	free(C);
	
	printf("time taken for test2 version1 = %7.16f\n",time_taken);
}

void test2_version2()
{
	int *A = (int *)malloc(1000000*sizeof(int));
	int *B = (int *)malloc(1000000*sizeof(int));
	int *C = (int *)malloc(1000000*sizeof(int));

	assert (A != NULL);
	assert (B != NULL);
	assert (C != NULL);

	for(int i=0;i<1000000;i++)
	{
		A[i] = rand()%100000;
		B[i] = rand()%100000;
	}

	double total_time = 0;

	for(int t = 0; t < 10; t++)
	{
		clear_cache();
		
		double t1 = get_clock();

		for(int i=0;i<250000;i++)
		{
			C[4*i] = A[4*i]+B[4*i];
			C[4*i+1] = A[4*i+1]+B[4*i+1];
			C[4*i+2] = A[4*i+2]+B[4*i+2];
			C[4*i+3] = A[4*i+3]+B[4*i+3];
		}

		double t2 = get_clock();

		total_time += (t2-t1);
	}

	double time_taken = total_time/10;

	free(A);
	free(B);
	free(C);

	printf("Time taken for test2 version2 = %7.16f\n",time_taken);
}	


