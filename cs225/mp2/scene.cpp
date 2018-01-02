#include "image.h"
#include "scene.h"
#include <iostream>

Scene::Scene(int max)
{
	lengthOfArray = max;
	arrayOfPointerImages = new Image * [lengthOfArray];
	xcoords = new int[lengthOfArray];
	ycoords = new int[lengthOfArray];
	for(int a = 0; a < lengthOfArray; a++)
	{
		arrayOfPointerImages[a] = NULL;
		xcoords[a] = 0;
		ycoords[a] = 0;
	}
}

Scene::Scene( const Scene & source )
{
	copy(source);
}

Scene::~Scene()
{
	clear();
}

void Scene::copy( const Scene & source )
{
	lengthOfArray = source.lengthOfArray;
	arrayOfPointerImages = new Image * [source.lengthOfArray];
	xcoords = new int[source.lengthOfArray];
	ycoords = new int[source.lengthOfArray];
	for (int a = 0; a < lengthOfArray; a++)
	{
		if(source.arrayOfPointerImages[a] == NULL)
		{
			arrayOfPointerImages[a] = NULL;
			xcoords[a] = 0;
			ycoords[a] = 0;
		}
		else
		{
			arrayOfPointerImages[a] = new Image(*(source.arrayOfPointerImages[a]));
			xcoords[a] = source.xcoords[a];
			ycoords[a] = source.ycoords[a];
		}
	}
}// end of the copy definition method.

const Scene& Scene :: operator=(const Scene&source)
{
	if( &source == this )
	{
		return *this;
	}

	clear();
	copy(source);
	return *this;
}// end of the operator=(const Scene&source) method

void Scene :: clear()
{
	delete []xcoords;
	delete []ycoords;
	for( int a = 0; a < lengthOfArray ; a++)
	{
		if( arrayOfPointerImages[a] != NULL )
		{
			delete arrayOfPointerImages[a];
			arrayOfPointerImages[a] = NULL;
		}
	}
	delete []arrayOfPointerImages;
	arrayOfPointerImages = NULL;
}// end of the clear method

void Scene :: changemaxlayers( int newmax)
{
	if( newmax < lengthOfArray || newmax <= 0 )
	{
		std::cout << "invalid index" << endl;
		return;
	}
	if(newmax == lengthOfArray)
	{
		return;
	}
	Image ** tempArrayOfPointerImages = new Image * [newmax];
	int * xsub = new int[newmax];
	int * ysub = new int[newmax];
	for ( int a = 0; a < lengthOfArray; a++)
	{
		tempArrayOfPointerImages[a] = arrayOfPointerImages[a];
		xsub[a] = xcoords[a];
		ysub[a] = ycoords[a];
	}
	for (int a = lengthOfArray; a < newmax; a++)
	{
		tempArrayOfPointerImages[a] = NULL;
		xsub[a] = 0;
		ysub[a] = 0;
	}
	delete []arrayOfPointerImages;
	delete []xcoords;
	delete []ycoords;
	arrayOfPointerImages = tempArrayOfPointerImages;
	xcoords = xsub;
	ycoords = ysub;
	lengthOfArray = newmax;
}// end of the changemaxlayers method.

void Scene :: addpicture(const char *FileName, int index, int x, int y)
{
	if (index < 0 || index >= lengthOfArray)
	{
		std::cout << "The given index is out of bounds" << endl;
		return;
	}
	arrayOfPointerImages[index] = new Image;
	arrayOfPointerImages[index] -> readFromFile( FileName );
	xcoords[index] = x;
	ycoords[index] = y;
}// end of the addpicture method

void Scene :: changelayer(int index, int newindex)
{
	if( index == newindex )
	{
		return;
	}

	if(index < 0 || index >= lengthOfArray || newindex < 0 || newindex >= lengthOfArray)
	{
		std::cout << "Invalid Index value" << endl;
		return;
	}

	if( arrayOfPointerImages[newindex] != NULL)
	{
		delete arrayOfPointerImages[newindex];
	}

	xcoords[newindex] = xcoords[index];
	ycoords[newindex] = ycoords[index];
	arrayOfPointerImages[newindex] = arrayOfPointerImages[index];
	arrayOfPointerImages[index] = NULL;
	xcoords[index] = 0;
	ycoords[index] = 0;

}// end of changelayer method

/**
* Translates the x and y coordinate to a certain index and x and y point.
*/
void Scene :: translate( int index, int x, int y )
{
	if ((index >= 0 && index < lengthOfArray) && (arrayOfPointerImages[index] != NULL))
	{
		xcoords[index] = x;
		ycoords[index] = y;
	}
}

/**
* This method deletes the picture at a certain index.
*/
void Scene :: deletepicture( int index )
{
	if( index < 0 || index >= lengthOfArray )
	{
		std::cout << "Index that was passed through was invalid" << endl;
		return;
	}
	if( arrayOfPointerImages[index] != NULL)
	{
		delete(arrayOfPointerImages[index]);
		arrayOfPointerImages[index] = NULL;
	}
}

/**
* This method return a pointer to one of the images that was requested a certain index
*/
Image * Scene :: getpicture(int index) const
{
	if(index < 0 || index >= lengthOfArray || arrayOfPointerImages[index] == NULL)
	{
		return NULL;
	}
	return arrayOfPointerImages[index];
}

Image Scene :: drawscene() const
{
	unsigned long currentWidth = 0;
	unsigned long currentHeight = 0;
	for ( int a = 0; a < lengthOfArray; a++)
	{
		if( arrayOfPointerImages[a] != NULL )
		{
			if(currentHeight < (arrayOfPointerImages[a] ->height() + ycoords[a]))
			{
				currentHeight = arrayOfPointerImages[a] -> height() + ycoords[a];
			}
			if(currentWidth < (arrayOfPointerImages[a] -> width() + xcoords[a]))
			{
				currentWidth = arrayOfPointerImages[a] -> width() + xcoords[a];
			}
		}
	}


	Image final_image;
	final_image.resize(currentWidth, currentHeight);

	for( int b = 0; b < lengthOfArray; b++)
	{
		if(arrayOfPointerImages[b] != NULL)
		{
			for( size_t xx = 0; xx < arrayOfPointerImages[b]->width(); xx++)
			{
				for( size_t yy = 0; yy < arrayOfPointerImages[b]->height(); yy++)
				{
					*final_image( xcoords[b]+xx, ycoords[b]+yy) = *(*arrayOfPointerImages[b])(xx,yy) ;
				}
			}
		}
	}

	return final_image;
}
