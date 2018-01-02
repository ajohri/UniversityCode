#include "image.h"
#include "rgbapixel.h"
#include "png.h"

void Image::flipleft()
{
	//this->width() is getting the width from the PNG class and is a logical equivilant to super in java(sorta)
	int imageWidth = (*this).width(); 
	//this->height() is getting the height from the PNG class and is a logical equivilant to super in java(sorta)
	int imageHeight = (*this).height();
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth/2; x++)
		{
			// The first * goes up to the PNG class the second * is allowing you to get the pointer for that PNG object.
			RGBAPixel swapValue = *(*this)(imageWidth-x-1,y);
			*(*this)(imageWidth-x-1,y)=*(*this)(x,y);
			*(*this)(x,y)= swapValue;
		}
	}
}

void Image::adjustbrightness( int r, int g, int b)
{
	int imageWidth = this->width();
	int imageHeight = this->height();
	for(int x = 0; x < imageWidth; x++)
	{
		for(int y = 0; y < imageHeight; y++)
		{
			int red = (*this)(x,y) -> red;
			int green = (*this)(x,y) -> green;
			int blue = (*this)(x,y) -> blue;
			if( red + r < 256 && red + r >= 0)
			{
				(*this)(x,y) -> red = red + r;
			}
			else if(red + r > 255)
			{
				(*this)(x,y) -> red = 255;
			}
			else
			{
				(*this)(x,y) -> red = 0;
			}// This is all for the color red.

			if( green + g < 256 && green + g >= 0)
			{
				(*this)(x,y) -> green = green + g;
			}
			else if(green + g > 255)
			{
				(*this)(x,y) -> green = 255;
			}
			else
			{
				(*this)(x,y) -> green = 0;
			} // This is all for the color green.

			if(blue + b < 256 && blue + b >= 0)
			{
				(*this)(x,y) -> blue = blue + b;
			}
			else if(blue + b > 225)
			{
				(*this)(x,y) -> blue = 255;
			}
			else
			{
				(*this)(x,y) -> blue = 0;
			}
		}
	}
}	


void Image::invertcolors()
{
	int imageWidth = this->width();
	int imageHeight = this->height();
	for(int x = 0; x < imageWidth; x++)
	{
		for(int y = 0; y < imageHeight; y++)
		{
			// This is getting the red value at a certain (x,y) position via the (*)
			(*this)(x,y)->red = 255 - (*this)(x,y)->red;
			(*this)(x,y)->green = 255 - (*this)(x,y)->green;
			(*this)(x,y)->blue = 255 - (*this)(x,y)->blue;
		}
	}
}
