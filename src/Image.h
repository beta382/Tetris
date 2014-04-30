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
        Image(string filename = "");

        void setFileName(string fileName);
        
        /* ---------- Overriding from Drawable ---------- */
        int getWidth() const;
        int getHeight() const;
        
        /* ---------- Implemented from Drawable ---------- */

        void draw();
        void erase();
};

string getName(int n);

#endif // IMAGE_H_INCLUDED
