#include <algorithm>
#include <iostream>
#include "rgbapixel.h"
#include "png.h"

using namespace std;


PNG rotate(PNG original)
{
	size_t width = original.width();
	size_t height = original.height();
	PNG copy = PNG(width, height);
	for(size_t x = 0; x < width; x++)
	{
		for(size_t y = 0; y < height; y++)
		{
			*copy(x, y) = *original(width-1-x, height-1-y);
		}
	}
	return copy;
}



int main()
{
	
	PNG image("in.png");
	image = rotate(image);

	image.writeToFile("out.png");
	return 0;
}
