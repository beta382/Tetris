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

GhostBlock::GhostBlock(int x, int y, int size, int padding, unsigned int foreground, unsigned int background):
        Block(x, y, size, padding, foreground, background) {}

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
    
    // ExplodingBlock example, needs <ctime> and "Rectangle.h"
    /*
    // Make a big explosion block
    
    int explosionX = (x >= 2) ? getLocationX()-getTotalSize()*2 : getLocationX()-getTotalSize()*x;
    
    int explosionY = (y >= 2) ? getLocationY()-getTotalSize()*2 : getLocationY()-getTotalSize()*y;
    
    int explosionWidth;
    
    if (x >= 2 && (blockField.size()-x-1) >= 2) {
        explosionWidth = getTotalSize()*5-getPadding();
    } else if (x >= 2) {
        explosionWidth = getTotalSize()*(blockField.size()-x+2)-getPadding();
    } else {
        explosionWidth = getTotalSize()*(x+3)-getPadding();
    }

    int explosionHeight;
    if (y >= 2 && (blockField[0].size()-y-1) >= 2) {
        explosionHeight = getTotalSize()*5-getPadding();
    } else if (y >= 2) {
        explosionHeight = getTotalSize()*(blockField.size()-y+2)-getPadding();
    } else {
        explosionHeight = getTotalSize()*(y+3)-getPadding();
    }
    
    MyRectangle explosion(explosionX, explosionY, explosionWidth, explosionHeight, Color::RED, getBackground());
    
    // Blink two times
    for (int r = 0; r < 3; r++) {
        explosion.draw();
        
        g->Draw(); // Force screen redraw

        clock_t start = clock();
        
        while (clock() < start+150); // Wait 150ms
        
        explosion.erase();
        
        g->Draw(); // Force screen redraw

        start = clock();
        
        while (clock() < start+150); // Wait 150ms
    }
    
    // Actually clear the blocks
    for (int i = x-2; i <= x+2; i++) {
        for (int j = y-2; j <= y+2; j++) {
            if (i >= 0 && i < (int)blockField.size() && j >= 0 && j < (int)blockField[i].size() && blockField[i][j]) {
                blockField[i][j]->erase();
                
                Block *tmp = blockField[i][j];
                blockField[i][j] = NULL;
                
                tmp->doOnClear(blockField, i, j);
                delete tmp;
            }
        }
    }
    
    //*/

    // GravityBlock example, needs <ctime>
    /*
    bool didFall = true;
    while (didFall) {
        didFall = false;
        
        for (unsigned int i = 0; i < blockField.size(); i++) {
            for (unsigned int j = 1; j < blockField[i].size(); j++) {
                if (blockField[i][j] && !blockField[i][j-1]) {
                    blockField[i][j]->erase();
                    blockField[i][j-1] = blockField[i][j];

                    blockField[i][j] = NULL;
                    
                    blockField[i][j-1]->setLocation(blockField[i][j-1]->getLocationX(), 
                            blockField[i][j-1]->getLocationY()-blockField[i][j-1]->getTotalSize());
                    blockField[i][j-1]->draw();
                    
                    didFall = true;
                }
            }
        }
        
        g->Draw(); // Force screen redraw
        
        if (didFall) {
            clock_t start = clock();
            
            while (clock() < start + 100);
        }
    }
    //*/
}

GhostBlock *GhostBlock::makeNewClone() {
    GhostBlock *tmp = new GhostBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
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
        g->setColor(getBackground());
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
