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


/* ---------- Overriding from Block ---------- */

void GhostBlock::doOnClear(myVector<myVector<Block *> >& blockField, int x, int y) {
    // Do nothing
    
    // ExplodingBlock example
    /*for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if (i >= 0 && i < blockField.getSize() && j >= 0 && j < blockField[i].getSize() && blockField[i][j]) {
                delete blockField[i][j];
                blockField[i][j] = NULL;
            }
        }
    }*/
    
    // GravityBlock example, needs <ctime>
    /*bool didFall = true;
    while (didFall) {
        didFall = false;
        
        for (int i = 0; i < blockField.getSize(); i++) {
            for (int j = 0; j < blockField[i].getSize(); j++) {
                if (j-1 >= 0 && blockField[i][j] && !blockField[i][j-1]) {
                    blockField[i][j-1] = blockField[i][j]->makeNewClone();

                    delete blockField[i][j];
                    blockField[i][j] = NULL;
                    
                    blockField[i][j-1]->setLocation(blockField[i][j-1]->getLocationX(), 
                            blockField[i][j-1]->getLocationY()-blockField[i][j-1]->getTotalSize());
                    blockField[i][j-1]->draw();
                    
                    didFall = true;
                }
            }
        }
        
        g->Draw();
        
        if (didFall) {
            clock_t start = clock();
            
            while (clock() < start + 250);
        }
    }*/
}

GhostBlock *GhostBlock::makeNewClone() {
    return new GhostBlock(*this);
}


void GhostBlock::draw() {
    g->setColor(getForeground());
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
