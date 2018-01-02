/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) 
{
    solidColorPicker temporary = solidColorPicker(fillColor);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) 
{
    gridColorPicker temporary = gridColorPicker(gridColor, gridSpacing);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) 
{
    gradientColorPicker temporary = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) 
{
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) 
{
    solidColorPicker temporary = solidColorPicker(fillColor);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) 
{
    gridColorPicker temporary = gridColorPicker(gridColor, gridSpacing);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    gradientColorPicker temporary = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
    return fill(img, x, y, temporary, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) 
{
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) 
{
    // Getting the intial red green blue value at that specific point.
    int intial_red = img(x,y) -> red;
    int intial_blue = img(x,y) -> blue;
    int intial_green = img(x,y) -> green;
    
    // Getting the width of the image
    int width = img.width();
    int height = img.height();
    
    // A counter to make sure we parse through each of the pixels in image.
    int pixel_count = 0;
    // Need to create an animation object to use later in the code.
    animation A;

    // A 2-D array of boolean variables to make sure that we have visited each and every pixel
    bool ** compeleted = new bool *[width];

    // Intializing each index in the image to false so that we can visit them at a later time.
    for (int i = 0; i < width; i++)
    {
        compeleted[i] = new bool[height];
        for (int j = 0; j < height; j++)
        {
            compeleted[i][j] = false;
        }
    }

    OrderingStructure<int> xcoords;
    OrderingStructure<int> ycoords;

    xcoords.add(x);
    ycoords.add(y);

    while(!xcoords.isEmpty() && !ycoords.isEmpty())
    {
        int current_x = xcoords.remove();
        int current_y = ycoords.remove();

        if ( ((pow((img(current_x, current_y)->red - intial_red), 2)
             + pow((img(current_x, current_y)->green - intial_green), 2)
             + pow((img(current_x, current_y)->blue - intial_blue), 2) ) <= tolerance) && !compeleted[current_x][current_y])
        {
            *img(current_x,current_y) = fillColor(current_x,current_y);
            compeleted[current_x][current_y] = true;

            pixel_count++;

            if(pixel_count % frameFreq == 0)
            {
                A.addFrame(img);
            }

            // Adding right neighor
            if((current_x + 1) < width)
            {
                xcoords.add(current_x + 1);
                ycoords.add(current_y);
            }

            // Adding down neighbor
            if((current_y + 1) < height)
            {
                xcoords.add(current_x);
                ycoords.add(current_y + 1);
            }

            // Adding left neighbor
            if((current_x - 1) >= 0)
            {
                xcoords.add(current_x - 1);
                ycoords.add(current_y);
            }

            // Adding up neighbor
            if((current_y - 1) >= 0)
            {
                xcoords.add(current_x);
                ycoords.add(current_y -1);
            }

        }
    }
    for(int i = 0; i < width; i++)
    {
        delete [] compeleted[i];
    }
    delete [] compeleted;

    return A;
}