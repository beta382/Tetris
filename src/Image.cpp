/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "Image.h"

//Contructor, can set fileName from here
Image::Image(string fileName):
Drawable()
{
    if (fileName != "") {
        setFileName(fileName);
    }
}

//Tells image object the file to open, which it will later display
void Image::setFileName(string fileName)
{
    image.ReadFromFile(fileName.c_str());
}


/* ---------- Overriding from Drawable ---------- */

//Returns width of image
int Image::getWidth() const {
    return image.TellWidth();
}

//Returns height of image
int Image::getHeight() const {
    return image.TellHeight();
}


/* ---------- Implemented from Drawable ---------- */

//Draws image to screen using EasyBMP library
void Image::draw()
{
    for(int i = 0; i < getWidth(); i++)
    {
        for(int j = 0; j < getHeight(); j++)
        {
            //Loops through pixels in image file, getting their colors
            int red = image.GetPixel(i, j).Red;
            int green = image.GetPixel(i, j).Green;
            int blue = image.GetPixel(i, j).Blue;

            unsigned int rgb = ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);

            //cout << rgb << endl;
            
            
            //Displays pixel on screen
            g->setColor(rgb);

            g->plot(getLocationX()+i, getLocationY()+getHeight()-j);

            //cout << getLocationX()+i << " " << getLocationY()-j << endl;
        }
    }

    isVisible = true;
}

//Would erase images
void Image::erase()
{

}

//This function takes the number we want to display, 
// and turns it into a file name
string getName(int n)
{
    string name;
    
    if(n == 1) name = "img/1.bmp";
    else if(n == 2) name = "img/2.bmp";
    else if(n == 3) name = "img/3.bmp";
    else if(n == 4) name = "img/4.bmp";
    else if(n == 5) name = "img/5.bmp";
    else if(n == 6) name = "img/6.bmp";
    else if(n == 7) name = "img/7.bmp";
    else if(n == 8) name = "img/8.bmp";
    else if(n == 9) name = "img/9.bmp";
    else if(n == 0) name = "img/0.bmp";
    
    return name;
}
