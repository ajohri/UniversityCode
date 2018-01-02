/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    MosaicCanvas * final_mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, TileImage> tiles;
    vector< Point<3> > coordinates;
   
    Point<3> temp;
    for(size_t i = 0; i < theTiles.size(); i++)
    {
            RGBAPixel avgColor = theTiles[i].getAverageColor();
            temp = Point<3>(avgColor.red, avgColor.green, avgColor.blue);
            coordinates.push_back(temp);
            tiles[temp] = theTiles[i];
    }
    KDTree<3> kdTree(coordinates);
    for(int i = 0; i < theSource.getColumns(); i++)
    {
            for(int j = 0; j < theSource.getRows(); j++) 
            {
                    RGBAPixel temp = theSource.getRegionColor(j,i);
                    Point<3> start(temp.red, temp.green, temp.blue);
                    Point<3> end = kdTree.findNearestNeighbor(start);
                    final_mosaic->setTile(j, i, tiles[end]);
            }
    }
    return final_mosaic;
}
