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
        
        void setWidth(int);
        int getWidth() const;
        void setHeight(int);
        int getHeight() const;
        
        virtual void setLocation(int x, int y);
        int getLocationX() const;
        int getLocationY() const;
        
        virtual void setForeground(unsigned int color);
        unsigned int getForeground() const;
        virtual void setBackground(unsigned int color);
        unsigned int getBackground();
        
        static void setG(GLUT_Plotter *);

        virtual ~Drawable() {};
    protected:
        Drawable();
        Drawable(int x, int y);
        Drawable(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        Drawable(const Drawable&);
        Drawable& operator =(const Drawable&);
        
        int x;
        int y;
        
        int width;
        int height;
        
        unsigned int foreground;
        unsigned int background;
        
        bool isVisible;

        static GLUT_Plotter *g;
};

#endif /* DRAWABLE_H_ */
