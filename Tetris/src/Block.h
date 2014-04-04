/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "Drawable.h"
#include "myVector.h"

// TODO: Make child classes for different blocks, i.e. GhostBlock, special Blocks, etc.
class Block: public Drawable {
    public:
        Block(GLUT_Plotter *g);
        Block(GLUT_Plotter *g, int x, int y);
        Block(GLUT_Plotter *g, int x, int y, int size, int padding);
        Block(const Block&);
        Block& operator =(const Block&);
        ~Block();
        
        int getSize() const;
        int getPadding() const;
        int getTotalSize() const;
        
        virtual void doOnClear(myVector<myVector<Block *> > *);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        int padding;
};

#endif /* BLOCK_H_ */
