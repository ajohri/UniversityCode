#include "matrix.h"
#include "papi_support.h"
#include <sys/time.h>


void clear_cache();


/*We have used papi to count the number of clock cycles. If this is
inconvenient for you, please feel free to use any other suitable
timing functions.*/

int main(int argc, char **argv)
{

  papi_init();


  papi_hw_details();

  papi_prepare_l1_counters();

 int num_rows = atoi(argv[1]);
 int num_cols = atoi(argv[2]);
 int block_size_x = atoi(argv[3]);
 int block_size_y = atoi(argv[4]);

 double *A = (double *)malloc(num_rows*num_cols*sizeof(double));
 double *B = (double *)malloc(num_rows*num_cols*sizeof(double));

 for(int i=0;i<num_rows;i++)
 {
 	for(int j=0;j<num_cols;j++)
	{
		B[i*num_cols+j] = rand()%1000;
	}
 }

 /*Example for PAPI usage -----*/
 long long diff = 0;
 long long tot_accesses = 0;
 long long tot_misses = 0;
 long long tot_hits = 0;

 // for(int i=0;i<5;i++)
 // {
 //
 // clear_cache();
 //
 //  long long start_cycles = PAPI_get_real_cyc();
 //
 //  long long cache_info[2];
 //  papi_start();
 //
 // basic_implementation(A,B,num_rows,num_cols);
 //
 // papi_stop_and_report(cache_info);
 //
 // tot_accesses += cache_info[1];
 // tot_misses += cache_info[0];
 // tot_hits += cache_info[1]-cache_info[0];
 //
 // long long end_cycles = PAPI_get_real_cyc();
 //
 // diff += (end_cycles-start_cycles);
 //
 // }
 //
 // tot_accesses /= 5;
 // tot_misses /= 5;
 // tot_hits /= 5;
 // diff /= 5;
 //
 // printf("Vanilla: Basic Time taken = %lld\n",diff);
 //
 // diff = 0;
 // tot_accesses = 0;
 // tot_misses = 0;
 // tot_hits = 0;
 //
 // for(int i=0;i<5;i++)
 // {
 //
 //  clear_cache();
 //  long long start_cycles = PAPI_get_real_cyc();
 //
 //  long long cache_info[2];
 //  papi_start();
 // basic_flipped(A,B,num_rows,num_cols);
 //  papi_stop_and_report(cache_info);
 //
 //  tot_accesses += cache_info[1];
 //  tot_misses += cache_info[0];
 //  tot_hits += cache_info[1]-cache_info[0];
 //
 //  long long end_cycles = PAPI_get_real_cyc();
 //
 //  diff += (end_cycles-start_cycles);
 //
 //  }
 //
 //  tot_accesses /= 5;
 //  tot_misses /= 5;
 //  tot_hits /= 5;
 //  diff /= 5;
 //
 //  printf("Flipped: Basic Time taken = %lld\n",diff);
 //
 //  diff = 0;
 //  tot_accesses = 0;
 //  tot_misses = 0;
 //  tot_hits = 0;
 //
 //
 // for(int i=0;i<5;i++)
 // {
 // 	clear_cache();
 //  long long start_cycles = PAPI_get_real_cyc();
 //
 //  long long cache_info[2];
 //  papi_start();
 // basic_unrolled_4(A,B,num_rows,num_cols);
 //  papi_stop_and_report(cache_info);
 //
 //  tot_accesses += cache_info[1];
 //  tot_misses += cache_info[0];
 //  tot_hits += cache_info[1]-cache_info[0];
 //
 //  long long end_cycles = PAPI_get_real_cyc();
 //
 //  diff += (end_cycles-start_cycles);
 //
 //  }
 //  tot_accesses /= 5;
 //  tot_misses /= 5;
 //  tot_hits /= 5;
 //  diff /= 5;
 //
 //  printf("Unroll 4: Basic Time taken = %lld\n",diff);
 //
 //  diff = 0;
 //  tot_accesses = 0;
 //  tot_misses = 0;
 //  tot_hits = 0;
 //
 //
 //  for(int i=0;i<5;i++)
 //  {
 //  	 clear_cache();
 //     long long start_cycles = PAPI_get_real_cyc();
 //
 //     long long cache_info[2];
 //     papi_start();
 //    basic_unrolled_8(A,B,num_rows,num_cols);
 //     papi_stop_and_report(cache_info);
 //
 //     tot_accesses += cache_info[1];
 //     tot_misses += cache_info[0];
 //     tot_hits += cache_info[1]-cache_info[0];
 //
 //     long long end_cycles = PAPI_get_real_cyc();
 //
 //     diff += (end_cycles-start_cycles);
 //
 //   }
 //   tot_accesses /= 5;
 //   tot_misses /= 5;
 //   tot_hits /= 5;
 //   diff /= 5;
 //
 //   printf("Unroll 8: Basic Time taken = %lld\n",diff);
 //
 //   diff = 0;
 //   tot_accesses = 0;
 //   tot_misses = 0;
 //   tot_hits = 0;

   printf("THIS IS THE BLOCKING\n");
   for(int i=0;i<5;i++)
   {
      clear_cache();
      long long start_cycles = PAPI_get_real_cyc();
      long long cache_info[2];
      papi_start();
      basic_block(A,B,num_rows,num_cols,block_size_x,block_size_y);
      papi_stop_and_report(cache_info);

      tot_accesses += cache_info[1];
      tot_misses += cache_info[0];
      tot_hits += cache_info[1]-cache_info[0];

      long long end_cycles = PAPI_get_real_cyc();

      diff += (end_cycles-start_cycles);

   }

   tot_accesses /= 5;
   tot_misses /= 5;
   tot_hits /= 5;
   diff /= 5;

   printf("BLOCKING: Basic Time taken = %lld\n",diff);


 free(A);
 free(B);

}

void clear_cache()
{
	double *A = (double *)malloc(4096*4096*sizeof(double));
	assert (A != NULL);

	for(int i=0;i<4096*4096;i++)
	{
		A[i] = 2*i;
	}

	double sum = 0;

	for(int i=0;i<4096*4096;i++)
		sum += A[i];

	free(A);
}
