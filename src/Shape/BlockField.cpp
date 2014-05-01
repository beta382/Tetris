/*
 * BlockField.cpp
 *
 *  Created on: May 1, 2014
 *      Author: Austin
 */

#include "BlockField.h"

BlockField::BlockField():
Shape()
{
}

BlockField::BlockField(int x, int y, int width, int height, int blockSize, int padding, 
        unsigned int background):
Shape(x, y, blockSize, padding, background)
{
    setWidth(width);
    setHeight(height);
    blocks = vector<Block*>(width*height, static_cast<Block*>(NULL));
}

void BlockField::set(int x, int y, Block* block) {
    if (blocks[x+y*width]) {
        delete blocks[x+y*width];
    }
    
    blocks[x+y*width] = block;
}

Block* BlockField::get(int x, int y) const {
    return blocks[x+y*width];
}


Block*& BlockField::at(int x, int y) {
    return blocks[x+y*width];
}

int BlockField::getInternalWidth() {
    return width;
}

int BlockField::getInternalHeight() {
    return height;
}
