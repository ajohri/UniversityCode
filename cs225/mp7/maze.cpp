#include "maze.h"
#include <cstdlib>
#include <algorithm>

//make dat maze doh
void SquareMaze::makeMaze(int width_parameter, int height_parameter){
	//variables dood
	this->width = width_parameter;
	this->height = height_parameter;

	//much sets such disjoint
	DisjointSets sets;
	sets.addelements(width*height);

	//puttin' up walls isn't right, man
	cells = std::vector<Cell>();
	int it = 0;
	while(it<width*height){
		cells.push_back(Cell());
		it++;
	}

	//makin' dem walls random 'n stuff
	std::vector<int> tmp;
	it = 0;
	while(it<cells.size()*2){
		tmp.push_back(it);
		it++;
	}

	srand(time(NULL));
	std::random_shuffle(tmp.begin(), tmp.end()); //algo rythms
	for(std::vector<int>::iterator i = tmp.begin();i !=tmp.end(); i++){
		if(*i <cells.size()){
			if((*i+1)%width != 0){
				if(sets.find(*i) != sets.find(*i+1)){
					sets.setunion(*i, *i+1);
					cells[*i].right=0;
				}
			}
		}
		else{
			int cell = *i - cells.size();
			if(cell<(height-1)*width){
				if(sets.find(cell) != sets.find(cell+width)){
					sets.setunion(cell, cell+width);
					cells[cell].bottom = 0;
				}
			}
		}
	}

}

//canTravel()
//can you travel?  well can you?
bool SquareMaze::canTravel(int x, int y, int dir) const{
	if(dir==0){
		if(x==width-1)
			return 0;
		return !cells[idx(x,y)].right;
	}
	if(dir==1){
		if(y==height-1)
			return 0;
		return !cells[idx(x,y)].bottom;
	}
	if(dir==2){
		if(x==0)
			return 0;
		return !cells[idx(x,y)-1].right;
	}
	if(dir==3){
		if(y==0)
			return 0;
		return !cells[idx(x,y)-width].bottom;
	}
	return 0;
}

//i want my wall to be set yo
void SquareMaze::setWall(int x, int y, int dir, bool exists){
	if(dir==0)
		cells[idx(x,y)].right = exists;
	else if(dir==1)
		cells[idx(x,y)].bottom = exists;
}

//solve the maze!!!
vector<int> SquareMaze::solveMaze(){
	vector<int> solution = DFS(0,0,3);
	if(!solution.empty() && solution.back() ==-1)
		solution.erase(solution.end()-1);
	return solution;
}

std::vector<int> SquareMaze::DFS(int x, int y, int fromdir) const{
 	if (y == height-1) // bottom edge?
    {
        if (fromdir == 0 && !(canTravel(x, y, 3) || canTravel(x, y, 2)))
            return std::vector<int>(1,-1);
        else if (fromdir == 2 && !(canTravel(x, y, 0) || canTravel(x, y, 3)))
            return std::vector<int>(1,-1);
        else if (fromdir == 3 && !(canTravel(x, y, 0) || canTravel(x, y, 2)))
            return std::vector<int>(1,-1);
    }

    // RECURSIVE CASE:
    //
    // this vector holds all paths to bottom row from this node
    std::vector<std::vector<int> > paths;
    std::vector<int> tmp;

    // try to traverse in each direction we didn't come from
    // no other markers are needed to mark visited nodes since
    // the graph is garaunteed to be noncyclic
    if (fromdir != 0 && canTravel(x, y, 0)) // right?
    {
        tmp = DFS(x+1, y, 2);
        if(!tmp.empty() && tmp.back() == -1)
        {
            tmp.insert(tmp.begin(),1,0);
            paths.push_back(tmp);
        }
    }
    if (fromdir != 1 && canTravel(x, y, 1)) // down?
    {
        tmp = DFS(x, y+1, 3);
        if(!tmp.empty() && tmp.back() == -1)
        {
            tmp.insert(tmp.begin(),1,1);
            paths.push_back(tmp);
        }
    }
    if (fromdir != 2 && canTravel(x, y, 2)) // left?
    {
        tmp = DFS(x-1, y, 0);
        if(!tmp.empty() && tmp.back() == -1)
        {
            tmp.insert(tmp.begin(),1,2);
            paths.push_back(tmp);
        }
    }
    if (fromdir != 3 && canTravel(x, y, 3)) // up?
    {
        tmp = DFS(x, y-1, 1);
        if(!tmp.empty() && tmp.back() == -1)
        {
            tmp.insert(tmp.begin(),1,3);
            paths.push_back(tmp);
        }
    }

    // pick the longest path to bottom found and return it
    // if we hit a dead end, an empty vector is returned
    // if there were no paths. return an empty vector.
    std::vector<int> longest; // empty vector. size 0.

    // if this could be an endpoint, we need to indicate that in the return
    // value if no other suitible paths were found.
    if (y == height-1)
    {
        longest = std::vector<int>(1,-1);
    }

    for(std::vector<std::vector<int> >::iterator i = paths.begin();
            i != paths.end(); i++)
    {
        if (i->size() > longest.size())
            longest = *i;
    }
    return longest;
}

PNG* SquareMaze::drawMaze() const{
	PNG* ret = new PNG(width*10+1, height*10+1);

	for(int i=0; i<ret->height(); i++){
		(*ret)(0,i)->red = 0;
		(*ret)(0,i)->green = 0;
		(*ret)(0,i)->blue = 0;
	}
	for(int i = 10; i<ret->width(); i++){
		(*ret)(i,0)->red = 0;
		(*ret)(i,0)->green = 0;
		(*ret)(i,0)->blue = 0;
	}
	for(int i=0; i<cells.size(); i++)
    {
        if(cells[i].right)
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)((i%width+1)*10,(i/width)*10+k)->red = 0;
                (*ret)((i%width+1)*10,(i/width)*10+k)->green = 0;
                (*ret)((i%width+1)*10,(i/width)*10+k)->blue = 0;
            }
        }
        if(cells[i].bottom)
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)((i%width)*10+k, (i/width+1)*10)->red = 0;
                (*ret)((i%width)*10+k, (i/width+1)*10)->green = 0;
                (*ret)((i%width)*10+k, (i/width+1)*10)->blue = 0;
            }
        }
    }

    return ret;
	
}

PNG* SquareMaze::drawMazeWithSolution() 
{
    PNG* ret = drawMaze();
    int current_x = 5;
    int current_y = 5;
	vector<int> solution = solveMaze();

    // draw the path itself
    for(std::vector<int>::const_iterator i = solution.begin();
            i != solution.end(); i++)
    {
        if(*i == 0) // right
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)(current_x, current_y)->red = 255;
                (*ret)(current_x, current_y)->green = 0;
                (*ret)(current_x, current_y)->blue = 0;
                current_x++;
            }
            current_x--;
        }
        else if (*i == 1) // down
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)(current_x, current_y)->red = 255;
                (*ret)(current_x, current_y)->green = 0;
                (*ret)(current_x, current_y)->blue = 0;
                current_y++;
            }
            current_y--;
        }
        else if (*i == 2) // left
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)(current_x, current_y)->red = 255;
                (*ret)(current_x, current_y)->green = 0;
                (*ret)(current_x, current_y)->blue = 0;
                current_x--;
            }
            current_x++;
        }
        else if (*i == 3) // up
        {
            for(int k=0; k<=10; k++)
            {
                (*ret)(current_x, current_y)->red = 255;
                (*ret)(current_x, current_y)->green = 0;
                (*ret)(current_x, current_y)->blue = 0;
                current_y--;
            }
            current_y++;
        }
    }

    // delete the exit wall
    current_x = current_x/10; // turn x into a cell number
    for (int k=1; k<=9; k++)
    {
        (*ret)(current_x*10+k, height*10)->red = 255;
        (*ret)(current_x*10+k, height*10)->green = 255;
        (*ret)(current_x*10+k, height*10)->blue = 255;
    }

    return ret;
}

// idx()
// returns the vector index of given x,y coordianate
// complexity: O(1)
// params:
//      int x - x coordinate
//      int y - y coordinate
// returns:
//      vector index of coordinate
int SquareMaze::idx(int x, int y) const
{
    return width*y+x;
}