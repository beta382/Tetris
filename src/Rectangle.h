/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Drawable.h"

class MyRectangle: public Drawable {
    public:
        MyRectangle();
        MyRectangle(int x, int y);
        MyRectangle(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        MyRectangle(const MyRectangle&);
        MyRectangle& operator =(const MyRectangle&);
        ~MyRectangle();
        
        int getWidth() const;
        int getHeight() const;
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
};

#endif /* RECTANGLE_H_ */
