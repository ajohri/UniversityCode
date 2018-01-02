#include <thread>
#include "list.h"
#include <vector>
#include <mutex>
#include <sys/time.h>
#include <chrono>

std::mutex list_mutex;
std::atomic<int> global(0);

int main(int argc, char **argv)
{

	int num_threads = atoi(argv[1]);
	int size = atoi(argv[2]);
	int num_insertions = atoi(argv[3]);
	int num_deletions = atoi(argv[4]);

	int num_insert = num_insertions;
	int num_delete = num_deletions;


	std::vector<std::thread> workers(num_threads);

	list *l = (list *)malloc(sizeof(list));
	assert (l != NULL);

	init_list(size,l);

	auto start_time = std::chrono::high_resolution_clock::now();

	//std::cout <<" start = "<<start_time.count()<<std::endl;

	int seed = 0;
	for(int i=0;i<num_threads;i++)
	{
		thread_param start_tp;
		start_tp.seed = seed;
		start_tp.num_insertions = num_insertions;
		start_tp.num_deletions = num_deletions;
		std::thread tmp{[l,&start_tp]{driver(l,start_tp);}};
		workers[i] = std::move(tmp);

		seed++;
	}

	for(int i=0;i<num_threads;i++) workers[i].join();

	std::chrono::high_resolution_clock::duration diff = std::chrono::high_resolution_clock::now()-start_time;

	std::cout<<"Time taken = "<<diff.count()<<std::endl;

	free(l);

}
