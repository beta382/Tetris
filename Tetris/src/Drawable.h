/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 31, 2014
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "GLUT_Plotter.h"
#include "drawkit.h"

#include <iostream>
#include <iomanip>

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
        
        virtual void setColor (unsigned int color);
        unsigned int getColor() const;
        
        virtual ~Drawable() {};
    protected:
        Drawable(GLUT_Plotter *g);
        Drawable(GLUT_Plotter *g, int x, int y);
        Drawable(GLUT_Plotter *g, int x, int y, int width, int height, int color = Color::WHITE);
        
        GLUT_Plotter *g;
        
        int x;
        int y;
        
        int width;
        int height;
        
        int color;
        
    public:bool isVisible;
};

#endif /* DRAWABLE_H_ */
