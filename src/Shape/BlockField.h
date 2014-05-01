/*
 * BlockField.h
 *
 *  Created on: May 1, 2014
 *      Author: Austin
 */

#ifndef BLOCKFIELD_H_
#define BLOCKFIELD_H_

#include "Shape.h"

class BlockField: public Shape {
_registerForLeakcheckWithID(BlockField)
    public:
        BlockField();
        BlockField(int x, int y, int width, int height, int blockSize, int padding, 
                unsigned int background = Color::BLACK);
        
        void set(int, int, Block*);
        Block* get(int, int) const;
        Block*& at(int x, int y);
        
        int getInternalWidth();
        int getInternalHeight();
};

#endif /* BLOCKFIELD_H_ */
