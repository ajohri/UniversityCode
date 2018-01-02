#include <thread>
#include "list.h"
#include <vector>
#include <mutex>

void driver(list *l, thread_param &tp)
{

	int insertions = tp.num_insertions;
	int deletions = tp.num_deletions;
	int tid = tp.seed;

	std::cout <<" driver :: seed = "<<tp.seed<<std::endl;

	while(insertions+deletions > 0)
	{
		int op = rand()%2;
		if(op==0 && insertions > 0) // insert
		{
			bool success = insert_node_lock(l,tid);
			if(success)
			{
				insertions--;
			}
		}
		else if(deletions > 0) // delete
		{
			bool success = delete_node_lock(l,tid);
			if(success) deletions--;
		}
	}

}

/*

	static int global = 0;

	function(){

	int local = 1;
	while(local ==1){
		atomicswap(&local, &global);
	}

	//code

	int local = 0;
	atomicswap(&local, %global);
	}
*/