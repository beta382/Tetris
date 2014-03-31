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

class Block: public Drawable {
    public:
        Block();
        Block(int x, int y);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
};

#endif /* BLOCK_H_ */
