/**
*  Class implementation of Disjoint sets
*/

#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for (int i = 0; i < num; i++)
	{
		array.push_back(-1);
	}
}

int DisjointSets::find(int elem)
{
	if(array[elem] < 0)
	{
		return elem;
	}
	else
	{
		return(array[elem] = find(array[elem]));
	}
}

void DisjointSets::setunion( int a, int b )
{
	int root_a=find(a);
	int root_b=find(b);
	if(root_a!=root_b)
	{
		if((-1)*array[root_a]<(-1)*array[root_b])
		{
			array[root_b]+=array[root_a];
			array[root_a]=root_b;
		}
		else
		{
			array[root_a]+=array[root_b];
			array[root_b]=root_a;
		}
	}
}