#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Drawable.h"
#include "EasyBMP.h"

class Image{
    Image();
    
    void setFileName(string fileName);
    void setXandY(int x, int y);
    void draw();
    void erase();
};

#endif // IMAGE_H_INCLUDED
