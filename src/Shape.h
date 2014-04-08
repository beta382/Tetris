/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 30, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Drawable.h"
#include <vector>
#include "Block.h"

class Shape: public Drawable {
    public:
        Shape(GLUT_Plotter *g);
        Shape(GLUT_Plotter *g, int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);
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
        
        Shape& addBlock(Block *const);
        
        /* ---------- Overriding from Drawable ---------- */
        void setLocation(int, int);
        void setForeground (unsigned int);
        void setBackground (unsigned int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        vector<Block *> blocks;
        
        int blockSize;
        int padding;
};

#endif /* SHAPE_H_ */
