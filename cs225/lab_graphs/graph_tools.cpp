/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
    queue< Vertex > line_path;
	line_path.push(start);
	unordered_map< Vertex, Vertex> pre_map; 
	pre_map.insert(make_pair(start, start));
	Vertex vert, x;
	while(!line_path.empty())
	{
		Vertex x = line_path.front();
		line_path.pop();
		if(x == end)
		{
			vert = x;
		}
		vector< Vertex > next = graph.getAdjacent(x);
		for(int i =0 ; i< next.size(); i++)
		{
			if(graph.getVertexLabel(next[i]) != "visited")
			{
				line_path.push(next[i]);
				graph.setVertexLabel(next[i], "visited");
				pre_map.insert(make_pair(next[i], x));
			}
		}
	}
	int incrementer = 0;
	while( vert != pre_map[vert])
	{
		x = pre_map[vert];
		graph.setEdgeLabel(x, vert, "MINPATH");
		vert = x; 
		incrementer++;
	}	
	return incrementer;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
    vector< Edge > store = graph.getEdges();
	int low = store[0].weight;
	int index = 0; 
	for( int i = 1; i < store.size(); i++)
	{
		if(store[i].weight < low )
		{
			low = store[i].weight;
			index = i; 
		}
	}
	Vertex origin = store[index].source; 
	Vertex final = store[index].dest; 
	graph.setEdgeLabel(origin, final, "MIN");
	return low;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector< Edge > Estore = graph.getEdges();
	vector< Vertex > Vstore = graph.getVertices();
	sort(Estore.begin(), Estore.end());
	DisjointSets d1;
	for(int i=0; i < Vstore.size(); i++)
	{
		d1.addelements(Vstore[i]);
	}
	for(int i=0; i < Estore.size(); i++)
	{
		Vertex r1 = Estore[i].source; 
		Vertex r2 = Estore[i].dest; 
		if(d1.find(r1) != d1.find(r2))
		{
			d1.setunion(r1, r2);
			graph.setEdgeLabel(r1, r2, "MST"); 
		}
	}
}
