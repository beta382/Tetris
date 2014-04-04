/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Block.h"

Block::Block (GLUT_Plotter *g): Drawable(g, 0, 0, 10, 10) {
    padding = 0;
}

Block::Block (GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 10, 10) {
    padding = 0;
}

Block::Block (GLUT_Plotter *g, int x, int y, int size, int padding): Drawable(g, x, y, size, size) {
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

void Block::doOnClear(myVector<myVector<Block *> > *blockField) {
    // Do nothing
}

Block *Block::makeNewClone() {
    return new Block(*this);
}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    g->setColor(getColor());
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

void Block::erase() {
    if (isVisible) {
        g->setColor(Color::BLACK);
        for (int i = 0; i < getSize(); i++) {
            for (int j = 0; j < getSize(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
