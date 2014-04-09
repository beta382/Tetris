/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr  8, 2014
 */

#include "Block.h"

Block::Block (): Drawable(0, 0, 10, 10) {
    padding = 0;
}

Block::Block (int x, int y): Drawable(x, y, 10, 10) {
    padding = 0;
}

Block::Block (int x, int y, int size, int padding, unsigned int foreground, unsigned int background):
        Drawable(x, y, size, size, foreground, background) {
    this->padding = padding;
}

Block::Block (const Block& other): Drawable(other) {
    padding = other.padding;
}

Block& Block::operator =(const Block& rhs) {
    if (this != &rhs) {
        Drawable::operator =(rhs);
        padding = rhs.padding;
    }
    
    return *this;
}

Block::~Block() {
    erase();
}

int Block::getSize() const {
    return width;
}

int Block::getPadding() const {
    return padding;
}

int Block::getTotalSize() const {
    return getSize()+getPadding();
}

void Block::doOnClear(vector<vector<Block *> >& blockField, int x, int y) {
    // Do nothing
}

Block *Block::makeNewClone() {
    return new Block(*this);
}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    g->setColor(getForeground());
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

void Block::erase() {
    if (isVisible) {
        g->setColor(getBackground());
        for (int i = 0; i < getSize(); i++) {
            for (int j = 0; j < getSize(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
