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

PlayingField::PlayingField(const PlayingField& other): Drawable(other) {
    init();
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blocks.at(i).at(j)) {
                blocks[i][i] = new Block(*(other.blocks.at(i).at(j)));
            }
        }
    }
}

PlayingField& PlayingField::operator =(const PlayingField& rhs) {
    if  (this != &rhs) {
        erase();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blocks[i][j]) {
                    delete blocks[i][j];
                }
            }
        }
        
        Drawable::operator =(rhs);
        
        init();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (rhs.blocks.at(i).at(j)) {
                    blocks[i][i] = new Block(*(rhs.blocks.at(i).at(j)));
                }
            }
        }
        
        draw();
    }
    
    return *this;
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
    Tetromino *tetromino = new Tetromino(g, getLocationX()+(BLOCK_SIZE+BLOCK_PADDING)*(getWidth()/2), 
            getLocationY()+(BLOCK_SIZE+BLOCK_PADDING)*getHeight(), BLOCK_SIZE, BLOCK_PADDING, type);
    
    // We spawn right above the field, this puts us at the top of the screen, properly centered
    tetromino->setLocation(tetromino->getLocationX()-tetromino->getTotalBlockSize()*((tetromino->getWidth()+1)/2),
            tetromino->getLocationY()-tetromino->getTotalBlockSize()*tetromino->getHeight());
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    // Probably return NULL if we can't spawn period, which would special-case a "game over"
    
    return tetromino;
}

void PlayingField::merge (Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = new Block(*(shape->getBlock(i)));
        blocks[(curBlock->getLocationX()-getLocationX())/curBlock->getTotalSize()]
              [(curBlock->getLocationY()-getLocationY())/curBlock->getTotalSize()] = curBlock;
    }
    
    delete shape;
    
    draw(); // TODO: Probably make a `void redraw()` eventually
}

bool PlayingField::canShiftUp(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()+tmp.getTotalSize());
                
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
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()-tmp.getTotalSize());
                
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
        tmp.setLocation(tmp.getLocationX()-tmp.getTotalSize(), tmp.getLocationY());
                
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
        tmp.setLocation(tmp.getLocationX()+tmp.getTotalSize(), tmp.getLocationY());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canRotateCW(Tetromino *const t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(t->getBlock(i));
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation(((tmp.getLocationY()-t->getLocationY())/tmp.getTotalSize()-t->getOffsetY()-t->getOffsetX())*
                  tmp.getTotalSize()+t->getLocationX(),
                (t->getWidth()-((tmp.getLocationX()-t->getLocationX())/tmp.getTotalSize()+t->getOffsetX())-1+
                  t->getOffsetY())*tmp.getTotalSize()+t->getLocationY());
        
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
        tmp.setLocation((t->getHeight()-((tmp.getLocationY()-t->getLocationY())/tmp.getTotalSize()-t->getOffsetY())-1-
                  t->getOffsetX())*tmp.getTotalSize()+t->getLocationX(),
                ((tmp.getLocationX()-t->getLocationX())/tmp.getTotalSize()+t->getOffsetX()+t->getOffsetY())*
                  tmp.getTotalSize()+t->getLocationY());
         
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
    if ((block->getLocationX()-getLocationX())/block->getTotalSize() < 0 || 
        (block->getLocationX()-getLocationX())/block->getTotalSize() >= getWidth() || 
        (block->getLocationY()-getLocationY())/block->getTotalSize() < 0 || 
        (block->getLocationY()-getLocationY())/block->getTotalSize() >= getHeight() ||
         blocks.at((block->getLocationX()-getLocationX())/block->getTotalSize())
               .at((block->getLocationY()-getLocationY())/block->getTotalSize()))
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
