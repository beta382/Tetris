/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "PlayingField.h"

PlayingField::PlayingField(): Drawable(0, 0, 10, 20) {
    for (int i = 0; i < getWidth(); i++) {
        myVector<Block *> tmp;
        blocks.pushBack(tmp);
        for (int j = 0; j < getHeight(); j++) {
            blocks[i].pushBack(NULL);
        }
    }
}

PlayingField::PlayingField(int x, int y, int width, int height): Drawable(x, y, width, height) {
    for (int i = 0; i < getWidth(); i++) {
        myVector<Block *> tmp;
        blocks.pushBack(tmp);
        for (int j = 0; j < getHeight(); j++) {
            blocks[i].pushBack(NULL);
        }
    }
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

Tetromino *PlayingField::spawnNewTetromino (int x, int y, TetrominoShape type) {
    Tetromino *tetromino = new Tetromino(getLocationX()+x, getLocationY()+y, type);
    
    return tetromino;
}

void PlayingField::merge (Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = new Block(shape->getBlock(i));
        blocks.at(curBlock->getLocationX()-getLocationX()).at(curBlock->getLocationY()-getLocationY()) = curBlock;
    }
    
    delete shape;
    
    draw();
}

bool PlayingField::canShiftUp(Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        Block curBlock = shape->getBlock(i);
        if (curBlock.getLocationY()-1 < getLocationY() ||
                blocks.at(curBlock.getLocationX()-getLocationX()).at(curBlock.getLocationY()-getLocationY()-1))
        {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftDown(Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        Block curBlock = shape->getBlock(i);
        if (curBlock.getLocationY()+1 >= getHeight()+getLocationY() ||
                blocks.at(curBlock.getLocationX()-getLocationX()).at(curBlock.getLocationY()-getLocationY()+1))
        {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftLeft(Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        Block curBlock = shape->getBlock(i);
        if (curBlock.getLocationX()-1 < getLocationX() ||
                blocks.at(curBlock.getLocationX()-getLocationX()-1).at(curBlock.getLocationY()-getLocationY()))
        {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftRight(Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        Block curBlock = shape->getBlock(i);
        if (curBlock.getLocationX()+1 >= getWidth()+getLocationX() ||
                blocks.at(curBlock.getLocationX()-getLocationX()+1).at(curBlock.getLocationY()-getLocationY()))
        {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canRotateCW(Tetromino *t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        Block tmp = t->getBlock(i);
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation(
                t->getHeight()-(tmp.getLocationY()-t->getLocationY()+t->getOffsetY())-1+
                  t->getLocationX()-t->getOffsetX(),
                (tmp.getLocationX()-t->getLocationX()+t->getOffsetX())+t->getLocationY()-t->getOffsetY());
        
        // Check that it isn't out-of-bounds or intersecting an existing Block
        if (tmp.getLocationX() < getLocationX() || tmp.getLocationX() >= getWidth()+getLocationX() || 
                tmp.getLocationY() < getLocationY() || tmp.getLocationY() >= getHeight()+getLocationY() ||
                blocks.at(tmp.getLocationX()-getLocationX()).at(tmp.getLocationY()-getLocationY()))
        {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canRotateCCW(Tetromino *t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        Block tmp = t->getBlock(i);
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation((tmp.getLocationY()-t->getLocationY()+t->getOffsetY())+t->getLocationX()-t->getOffsetX(),
                t->getWidth()-(tmp.getLocationX()-t->getLocationX()+t->getOffsetX())-1+
                  t->getLocationY()-t->getOffsetY());
    
        // Check that it isn't out-of-bounds or intersecting an existing Block
        if (tmp.getLocationX() < getLocationX() || tmp.getLocationX() >= getWidth()+getLocationX() || 
                tmp.getLocationY() < getLocationY() || tmp.getLocationY() >= getHeight()+getLocationY() ||
                blocks.at(tmp.getLocationX()-getLocationX()).at(tmp.getLocationY()-getLocationY()))
        {
            can = false;
        }
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
}

void PlayingField::erase() {
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                blocks[i][j]->erase();
            }
        }
    }
}
