/*
 * TetrominoBase.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Austin
 */

#include "TetrominoBase.h"

TetrominoBase::TetrominoBase(): Shape() {
    offsetX = 0;
    offsetY = 0;
}

TetrominoBase::TetrominoBase (int x, int y, int blockSize, int padding, unsigned int background):
        Shape(x, y, blockSize, padding, background)
{
    offsetX = 0;
    offsetY = 0;
}

TetrominoBase::TetrominoBase(const TetrominoBase& other): Shape(other) {
    offsetX = other.offsetX;
    offsetY = other.offsetY;
}

TetrominoBase& TetrominoBase::operator =(const TetrominoBase& rhs) {
    if (this != &rhs) {
        Shape::operator =(rhs);
        offsetX = rhs.offsetX;
        offsetY = rhs.offsetY;
    }
    
    return *this;
}

void TetrominoBase::rotateCW() {
    erase();
    for (unsigned int i = 0; i < blocks.size(); i++) {
        blocks[i]->setLocation(((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-getOffsetY()-
                  getOffsetX())*blocks[i]->getTotalSize()+getLocationX(),
                (getWidth()-((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+getOffsetX())-1+
                  getOffsetY())*blocks[i]->getTotalSize()+getLocationY());
    }
    draw();
    swap(width, height);
}

void TetrominoBase::rotateCCW() {
    erase();
    for (unsigned int i = 0; i < blocks.size(); i++) {
        blocks[i]->setLocation((getHeight()-((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-
                  getOffsetY())-1-getOffsetX())*blocks[i]->getTotalSize()+getLocationX(),
                ((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+getOffsetX()+getOffsetY())*
                  blocks[i]->getTotalSize()+getLocationY());
    }
    draw();
    swap(width, height);
}

int TetrominoBase::getOffsetX() const {
    return offsetX;
}

int TetrominoBase::getOffsetY() const {
    return offsetY;
}

