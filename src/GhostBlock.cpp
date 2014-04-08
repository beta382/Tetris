/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr  8, 2014
 */

#include "GhostBlock.h"

GhostBlock::GhostBlock(): Block() {}

GhostBlock::GhostBlock(int x, int y): Block(x, y) {}

GhostBlock::GhostBlock(int x, int y, int size, int padding): Block(x, y, size, padding) {}

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

void GhostBlock::doOnClear(vector<vector<Block *> >& blockField, int x, int y) {
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
            
            while (clock() < start + 100);
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
