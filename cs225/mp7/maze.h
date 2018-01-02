#ifndef _MAZE_H_
#define _MAZE_H_

#include "png.h"
#include "dsets.h"
#include <vector>

class SquareMaze{
	public:
		void makeMaze(int width, int height);

		bool canTravel(int x, int y, int dir) const;

		void setWall(int x, int y, int dir, bool exists);

		vector<int> solveMaze();

		PNG * drawMaze()const;

		PNG * drawMazeWithSolution();
	
	private:
		std::vector<int> DFS(int x, int y, int fromdir)const;

		int idx(int x, int y) const;

		class Cell{
			public:
				Cell(){
					right =1;
					bottom = 1;
				}
				bool right;
				bool bottom;
		};

		int width;
		int height;

		std::vector<Cell> cells;

};
#endif