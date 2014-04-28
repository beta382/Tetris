#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Drawable.h"
#include "../EasyBMP/EasyBMP.h"
#include <string>

class Image: public Drawable{
_registerForLeakcheckWithID(Image)
    private:
        BMP image;

    public:
        Image();

        void setFileName(string fileName);
        void setXandY(int x, int y);
        void draw();
        void erase();
};

#endif // IMAGE_H_INCLUDED
