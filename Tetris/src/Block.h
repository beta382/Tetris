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

const int BLOCK_SIZE = 10;

class Block: public Drawable {
    public:
        Block(GLUT_Plotter *g);
        Block(GLUT_Plotter *g, int x, int y);
        Block(GLUT_Plotter *g, int x, int y, int size);
        ~Block();
        
        int getSize() const;
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
};

#endif /* BLOCK_H_ */
