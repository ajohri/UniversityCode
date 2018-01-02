
#include "timers.h"

double get_clock()
{
	struct timeval tv;
	int ok;
	ok = gettimeofday(&tv,0);
	if(ok < 0)
	{
		printf("gettimeofday error");
		exit(-1);
	}
	return (tv.tv_sec*1.0+tv.tv_usec*1.0E-6);
}
