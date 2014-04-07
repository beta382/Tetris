/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 30, 2014
 * Date last modified:     Mar 30, 2014
 */

#include "Shape.h"

Shape::Shape(GLUT_Plotter *g): Drawable(g) {
    blockSize = 10;
    padding = 0;
}

Shape::Shape (GLUT_Plotter *g, int x, int y, int blockSize, int padding, unsigned int background): 
        Drawable(g, x, y, 0, 0, Color::WHITE, background)
{
    this->blockSize = blockSize;
    this->padding = padding;
}

Shape::Shape(const Shape& other): Drawable(other) {
    for (int i = 0; i < other.numBlocks(); i++) {
        if (other.blocks.at(i)) {
            addBlock(other.blocks.at(i)->makeNewClone());
        }
    }
    
    blockSize = other.blockSize;
    padding = other.padding;
}

Shape& Shape::operator =(const Shape& rhs) {
    if (this != &rhs) {
        erase();
        
        for (int i = 0; i < blocks.getSize(); i++) {
            delete blocks[i];
        }
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        
        for (int i = 0; i < rhs.numBlocks(); i++) {
            if (rhs.blocks.at(i)) {
                addBlock(rhs.blocks.at(i)->makeNewClone());
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

int Shape::getBlockSize() const {
    return blockSize;
}

int Shape::getPadding() const {
    return padding;
}

int Shape::getTotalBlockSize() const {
    return getBlockSize()+getPadding();
}

void Shape::shiftUp () {
    erase();
    setLocation(getLocationX(), getLocationY()+getTotalBlockSize());
    draw();
}

void Shape::shiftDown () {
    erase();
    setLocation(getLocationX(), getLocationY()-getTotalBlockSize());
    draw();
}

void Shape::shiftLeft () {
    erase();
    setLocation(getLocationX()-getTotalBlockSize(), getLocationY());
    draw();
}

void Shape::shiftRight () {
    erase();
    setLocation(getLocationX()+getTotalBlockSize(), getLocationY());
    draw();
}

Shape& Shape::addBlock(Block *const block) {
    blocks.pushBack(block);
    
    return *this;
}

/* ---------- Overriding from Drawable ---------- */

void Shape::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation(blocks[i]->getLocationX()+dX, blocks[i]->getLocationY()+dY);
    }
    
    this->x = x;
    this->y = y;
}

void Shape::setForeground (unsigned int foreground) {
    for (int i = 0; i < blocks.getSize(); i++){
        blocks[i]->setForeground(foreground);
    }
    
    this->foreground = foreground;
}

void Shape::setBackground(unsigned int background) {
    for (int i = 0; i < blocks.getSize(); i++){
        blocks[i]->setBackground(background);
    }
    
    this->background = background;
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
