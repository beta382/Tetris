/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "plotter.h"

class Drawable {
    public:
        virtual void draw() = 0;
        virtual void erase() = 0;
        
        void setWidth (int);
        int getWidth () const;
        void setHeight (int);
        int getHeight () const;
        
        virtual void setLocation (int x, int y);
        int getLocationX() const;
        int getLocationY() const;
        
        virtual void setColor (ink color);
        ink getColor() const;
        
        virtual ~Drawable() {};
    protected:
        Drawable();
        Drawable(int x, int y, int width, int height, ink color = white);
        
        Plotter p;
        
        int x;
        int y;
        
        int width;
        int height;
        
        ink color;
};

#endif /* DRAWABLE_H_ */
