/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 30, 2014
 * Date last modified:     Mar 30, 2014
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Drawable.h"
#include "myVector.h"
#include "Block.h"

class Shape: public Drawable {
    public:
        Shape(GLUT_Plotter *g);
        Shape(GLUT_Plotter *g, int x, int y);
        Shape(const Shape&);
        Shape& operator =(const Shape&);
        ~Shape();
        
        Block *getBlock(int) const;
        int numBlocks() const;
        
        void shiftUp();
        void shiftDown();
        void shiftLeft();
        void shiftRight();
        
        /* ---------- Inherited from Drawable ---------- */
        void setLocation(int, int);
        void setColor (unsigned int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        myVector<Block *> blocks;
};

#endif /* SHAPE_H_ */
