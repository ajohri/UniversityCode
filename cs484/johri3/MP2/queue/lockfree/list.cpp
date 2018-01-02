#include <thread>
#include "list.h"
#include <vector>
#include <mutex>

void driver(list *l, thread_param &tp)
{

	int insertions = tp.num_insertions;
	int deletions = tp.num_deletions;
	int tid = tp.seed;

	//std::cout <<" driver :: seed = "<<tp.seed<<std::endl;

	while(insertions+deletions > 0)
	{
		int op = rand()%2;
		if(op==0 && insertions > 0) // insert
		{
			bool success = insert_front_lf(l,tid);
			if(success)
			{
				insertions--;
			}
		}
		else if(deletions > 0) // delete
		{
			bool success = delete_back_lf(l,tid);
			if(success) deletions--;
		}
	}

}
