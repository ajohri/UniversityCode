#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "transpose.h"

// will be useful
// remember that you shouldn't go over SIZE
using std::min;

// modify this function to add tiling
void
transpose_tiled(int** src, int** dest) {
	for (int i = 0 ; i < SIZE ; i += SIZE/500) {
		for (int j = 0 ; j < SIZE ; j += SIZE/500) {
			for(int x = i; x < min(i + SIZE/500, SIZE); x++)
				for(int y = j; y < min(j + SIZE/500, SIZE); y++)
					dest[x][y] = src[y][x];
		}
	}
}	
