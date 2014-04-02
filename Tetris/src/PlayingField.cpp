/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "PlayingField.h"

PlayingField::PlayingField(GLUT_Plotter *g): Drawable(g, 0, 0, 10, 20) {
    init();
}

PlayingField::PlayingField(GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 10, 20) {
    init();
}

PlayingField::PlayingField(GLUT_Plotter *g, int x, int y, int width, int height): Drawable(g, x, y, width, height) {
    init();
}

PlayingField::~PlayingField() {
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                delete blocks[i][j];
            }
        }
    }
}

Tetromino *PlayingField::spawnNewTetromino (TetrominoShape type) {
    Tetromino *tetromino = new Tetromino(g, getLocationX()+(getWidth()/2)*BLOCK_SIZE, 
            getLocationY()+getHeight()*BLOCK_SIZE, type);
    
    // We spawn right above the field, to the right, this centers us and puts us at the top of the screen
    tetromino->setLocation(tetromino->getLocationX()-((tetromino->getWidth()/2)*BLOCK_SIZE),
            tetromino->getLocationY()-tetromino->getHeight()*BLOCK_SIZE);
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    
    return tetromino;
}

void PlayingField::merge (Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = new Block(*(shape->getBlock(i)));
        blocks[(curBlock->getLocationX()-getLocationX())/curBlock->getSide()]
              [(curBlock->getLocationY()-getLocationY())/curBlock->getSide()] = curBlock;
    }
    
    delete shape;
    
    draw();
}

bool PlayingField::canShiftUp(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()+tmp.getSide());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftDown(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()-tmp.getSide());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftLeft(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX()-tmp.getSide(), tmp.getLocationY());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftRight(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX()+tmp.getSide(), tmp.getLocationY());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

// TODO: Fix weird erasing
bool PlayingField::canRotateCW(Tetromino *const t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(t->getBlock(i));
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation(((tmp.getLocationY()-t->getLocationY())/tmp.getSide()-t->getOffsetY()-t->getOffsetX())*
                  tmp.getSide()+t->getLocationX(),
                (t->getWidth()-((tmp.getLocationX()-t->getLocationX())/tmp.getSide()+t->getOffsetX())-1+
                  t->getOffsetY())*tmp.getSide()+t->getLocationY());
        
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    return can;
}

bool PlayingField::canRotateCCW(Tetromino *const t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(t->getBlock(i));
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation((t->getHeight()-((tmp.getLocationY()-t->getLocationY())/tmp.getSide()-t->getOffsetY())-1-
                  t->getOffsetX())*tmp.getSide()+t->getLocationX(),
                ((tmp.getLocationX()-t->getLocationX())/tmp.getSide()+t->getOffsetX()+t->getOffsetY())*
                  tmp.getSide()+t->getLocationY());
         
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}


/* ---------- Private ---------- */

void PlayingField::init() {
    for (int i = 0; i < getWidth(); i++) {
        myVector<Block *> tmp;
        blocks.pushBack(tmp);
        for (int j = 0; j < getHeight(); j++) {
            // Everything that is a NULL pointer represents a blank space, makes checking for overlap super-simple,
            // just gotta add checks everywhere. Initialize all Block pointers to NULL
            blocks[i].pushBack(NULL);
        }
    }
}

bool PlayingField::couldAdd(Block *const block) const {
    bool can = true;
    
    // Check that it isn't out-of-bounds or intersecting an existing Block
    if ((block->getLocationX()-getLocationX())/block->getSide() < 0 || 
        (block->getLocationX()-getLocationX())/block->getSide() >= getWidth() || 
        (block->getLocationY()-getLocationY())/block->getSide() < 0 || 
        (block->getLocationY()-getLocationY())/block->getSide() >= getHeight() ||
         blocks.at((block->getLocationX()-getLocationX())/block->getSide())
               .at((block->getLocationY()-getLocationY())/block->getSide()))
    {
        can = false;
    }
    
    return can;
}

/* ---------- Inherited from Drawable ---------- */

void PlayingField::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                blocks[i][j]->setLocation(blocks[i][j]->getLocationX()+dX, blocks[i][j]->getLocationY()+dY);
            }
        }
    }
    
    draw();
    
    this->x = x;
    this->y = y;
}


/* ---------- Implemented from Drawable ---------- */

void PlayingField::draw() {
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                blocks[i][j]->draw();
            }
        }
    }
    
    isVisible = true;
}

void PlayingField::erase() {
    if (isVisible) {
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blocks[i][j]) {
                    blocks[i][j]->erase();
                }
            }
        }
        
        isVisible = false;
    }
}
