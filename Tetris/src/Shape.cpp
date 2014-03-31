/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 30, 2014
 * Date last modified:     Mar 30, 2014
 */

#include "Shape.h"

Shape::Shape(): Drawable(0, 0, 1, 1) {}

Shape::Shape (int x, int y): Drawable(x, y, 1, 1) {}

Shape::~Shape() {
    erase();
}

Block Shape::getBlock(int index) const {
    return blocks.at(index);
}

int Shape::numBlocks() const {
    return blocks.getSize();
}

void Shape::shiftUp () {
    erase();
    setLocation(getLocationX(), getLocationY()-1);
    draw();
}

void Shape::shiftDown () {
    erase();
    setLocation(getLocationX(), getLocationY()+1);
    draw();
}

void Shape::shiftLeft () {
    erase();
    setLocation(getLocationX()-1, getLocationY());
    draw();
}

void Shape::shiftRight () {
    erase();
    setLocation(getLocationX()+1, getLocationY());
    draw();
}


/* ---------- Inherited from Drawable ---------- */

void Shape::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i].setLocation(blocks[i].getLocationX()+dX, blocks[i].getLocationY()+dY);
    }
    
    this->x = x;
    this->y = y;
}

void Shape::setColor (ink color) {
    for (int i = 0; i < blocks.getSize(); i++){
        blocks[i].setColor(color);
    }
}


/* ---------- Implemented from Drawable ---------- */

void Shape::draw() {
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i].draw();
    }
}

void Shape::erase() {
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i].erase();
    }
}
