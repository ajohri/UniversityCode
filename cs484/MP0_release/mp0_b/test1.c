#include "timers.h"
#include "mp0_b.h"

void test1()
{
	double total_time= 0;

	for(int t=0;t<10;t++)
	{

		double t1 = get_clock();

        	int a = 2, a2 = 1;
        	for(int i=0;i<1000000;i++)
                	a2 = a*a;

        	double t2 = get_clock();

        	total_time +=( t2-t1);
	}

	double time_taken = total_time/10;

        printf("time taken for test1 = %7.16f\n",time_taken);
}

