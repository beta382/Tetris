/*
 * GhostBlock.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: Austin
 */

#include "GhostBlock.h"

GhostBlock::GhostBlock(GLUT_Plotter *g): Block(g) {}

GhostBlock::GhostBlock(GLUT_Plotter *g, int x, int y): Block(g, x, y) {}

GhostBlock::GhostBlock(GLUT_Plotter *g, int x, int y, int size, int padding): Block(g, x, y, size, padding) {}

GhostBlock::GhostBlock(const GhostBlock& other): Block(other) {}

GhostBlock& GhostBlock::operator =(const GhostBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}

GhostBlock::~GhostBlock() {
    erase();
}


/* ---------- Inherited from Block ---------- */

void GhostBlock::doOnClear(myVector<myVector<Block *> > *) {
    // Do nothing
}

GhostBlock *GhostBlock::makeNewClone() {
    return new GhostBlock(*this);
}


void GhostBlock::draw() {
    g->setColor(getColor());
    for (int i = 0; i < getWidth(); i++) {
        g->plot(getLocationX()+i, getLocationY());
        g->plot(getLocationX()+i, getLocationY()+getHeight()-1);
    }
    
    for (int i = 1; i < getHeight()-1; i++) {
        g->plot(getLocationX(), getLocationY()+i);
        g->plot(getLocationX()+getWidth()-1, getLocationY()+i);
    }
    
    isVisible = true;
}

void GhostBlock::erase() {
    if (isVisible) {
        g->setColor(Color::BLACK);
        for (int i = 0; i < getWidth(); i++) {
            g->plot(getLocationX()+i, getLocationY());
            g->plot(getLocationX()+i, getLocationY()+getHeight()-1);
        }
        
        for (int i = 1; i < getHeight()-1; i++) {
            g->plot(getLocationX(), getLocationY()+i);
            g->plot(getLocationX()+getWidth()-1, getLocationY()+i);
        }
        
        isVisible = false;
    }
}
