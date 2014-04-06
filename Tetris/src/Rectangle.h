/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Drawable.h"
#include "myVector.h"

class MyRectangle: public Drawable {
    public:
        MyRectangle(GLUT_Plotter *g);
        MyRectangle(GLUT_Plotter *g, int x, int y);
        MyRectangle(GLUT_Plotter *g, int x, int y, int width, int height, int color = Color::WHITE);
        MyRectangle(const MyRectangle&);
        MyRectangle& operator =(const MyRectangle&);
        ~MyRectangle();
        
        int getWidth() const;
        int getHeight() const;
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        int padding;
};

#endif /* RECTANGLE_H_ */
