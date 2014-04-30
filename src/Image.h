/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Drawable.h"

/*
What it does: Easy BMP is a C++ library created to read, write, and modify
              bitmap image files. In short, this library makes it easy to
              manipulate images in an OpenGL environment that has been
              stripped of funtctionality.
Why we use it: We use it to interpret image files that we want to display.
               This library is used to read in each pixel and get the color, 
               then we use our funtions to print that pixel to the screen.
Author: Paul Macklin
*/
#include "../EasyBMP/EasyBMP.h"

#include <string>

class Image: public Drawable{
_registerForLeakcheckWithID(Image)
    private:
        BMP image;

    public:
        //Contructor, can set fileName from here
        Image(string filename = "");

        //Tells image object the file to open, which it will later display
        void setFileName(string fileName);
        
        /* ---------- Overriding from Drawable ---------- */
        //Returns width of image
        int getWidth() const;
        //Returns height of image
        int getHeight() const;
        
        /* ---------- Implemented from Drawable ---------- */

        //Draws image to screen using EasyBMP library
        void draw();
        //Would erase images
        void erase();
};

//This function takes the number we want to display, 
// and turns it into a file name
string getName(int n);

#endif // IMAGE_H_INCLUDED
