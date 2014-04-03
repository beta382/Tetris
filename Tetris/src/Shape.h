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
        Shape(GLUT_Plotter *g, int x, int y, int blockSize, int padding);
        Shape(const Shape&);
        Shape& operator =(const Shape&);
        ~Shape();
        
        Block *getBlock(int) const;
        int numBlocks() const;
        
        int getBlockSize() const;
        int getPadding() const;
        int getTotalBlockSize() const;
        
        void shiftUp();
        void shiftDown();
        void shiftLeft();
        void shiftRight();
        
        // TODO: Eventually make a `Shape& addBlock(Block *const);`
        
        /* ---------- Inherited from Drawable ---------- */
        void setLocation(int, int);
        void setColor (unsigned int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        myVector<Block *> blocks;
        
        int blockSize;
        int padding;
};

#endif /* SHAPE_H_ */
