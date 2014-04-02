/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 30, 2014
 * Date last modified:     Mar 30, 2014
 */

#include "Shape.h"

Shape::Shape(GLUT_Plotter *g): Drawable(g) {}

Shape::Shape (GLUT_Plotter *g, int x, int y): Drawable(g, x, y) {}

Shape::Shape(const Shape& other): Drawable(other) {
    for (int i = 0; i < other.numBlocks(); i++) {
        if (other.blocks.at(i)) {
            blocks.pushBack(new Block(*(other.blocks.at(i))));
        }
    }
}

Shape& Shape::operator =(const Shape& rhs) {
    if (this != &rhs) {
        erase();
        
        for (int i = 0; i < blocks.getSize(); i++) {
            delete blocks[i];
        }
        
        Drawable::operator =(rhs);
        
        for (int i = 0; i < rhs.numBlocks(); i++) {
            if (rhs.blocks.at(i)) {
                blocks.pushBack(new Block(*(rhs.blocks.at(i))));
            }
        }
        
        draw();
    }
    
    return *this;
}

Shape::~Shape() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        delete blocks[i];
    }
}

Block *Shape::getBlock(int index) const {
    return blocks.at(index);
}

int Shape::numBlocks() const {
    return blocks.getSize();
}

void Shape::shiftUp () {
    erase();
    setLocation(getLocationX(), getLocationY()+BLOCK_SIZE);
    draw();
}

void Shape::shiftDown () {
    erase();
    setLocation(getLocationX(), getLocationY()-BLOCK_SIZE);
    draw();
}

void Shape::shiftLeft () {
    erase();
    setLocation(getLocationX()-BLOCK_SIZE, getLocationY());
    draw();
}

void Shape::shiftRight () {
    erase();
    setLocation(getLocationX()+BLOCK_SIZE, getLocationY());
    draw();
}


/* ---------- Inherited from Drawable ---------- */

void Shape::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation(blocks[i]->getLocationX()+dX, blocks[i]->getLocationY()+dY);
    }
    
    this->x = x;
    this->y = y;
}

void Shape::setColor (unsigned int color) {
    for (int i = 0; i < blocks.getSize(); i++){
        blocks[i]->setColor(color);
    }
}


/* ---------- Implemented from Drawable ---------- */

void Shape::draw() {
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->draw();
    }
    
    isVisible = true;
}

void Shape::erase() {
    if (isVisible) {
        for (int i = 0; i < blocks.getSize(); i++) {
            blocks[i]->erase();
        }
        
        isVisible = false;
    }
}
