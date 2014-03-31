/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "Tetromino.h"

Tetromino::Tetromino(): Shape(0, 0) {
    initTetromino(S); // Picked by fair dice roll, guaranteed to be random
}

Tetromino::Tetromino (int x, int y, TetrominoShape type): Shape(x, y) {
    initTetromino(type);
}

Tetromino::~Tetromino() {
    erase();
}


// TODO: Make these better, maybe fudge widths/heights?
void Tetromino::rotateCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i].setLocation(getHeight()-(blocks[i].getLocationY()-getLocationY()+offsetY)-1+getLocationX()-offsetX,
                (blocks[i].getLocationX()-getLocationX()+offsetX)+getLocationY()-offsetY);
    }
    draw();
    swap(width, height);
}

void Tetromino::rotateCCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i].setLocation((blocks[i].getLocationY()-getLocationY()+offsetY)+getLocationX()-offsetX,
                getWidth()-(blocks[i].getLocationX()-getLocationX()+offsetX)-1+getLocationY()-offsetY);
    }
    draw();
    swap(width, height);
}

int Tetromino::getOffsetX() const {
    return offsetX;
}

int Tetromino::getOffsetY() const {
    return offsetY;
}

/* ---------- Protected ---------- */

void Tetromino::initTetromino (TetrominoShape type) {
    Block block1, block2, block3, block4;
    
    switch (type) {
        case I:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX()+2, getLocationY());
            block4.setLocation(getLocationX()+3, getLocationY());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(cyan);
            setWidth(4);
            setHeight(3); // Fudged
            offsetX = 0;
            offsetY = 1;
            break;
        case O:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX(), getLocationY()+1);
            block4.setLocation(getLocationX()+1, getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(yellow);
            setWidth(2);
            setHeight(2);
            offsetX = 0;
            offsetY = 0;
            break;
        case T:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX()+2, getLocationY());
            block4.setLocation(getLocationX()+1, getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(magenta);
            setWidth(3);
            setHeight(3); // Fudged
            offsetX = 0;
            offsetY = 1;
            break;
        case J:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX()+2, getLocationY());
            block4.setLocation(getLocationX()+2, getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(blue);
            setWidth(3);
            setHeight(3); // Fudged
            offsetX = 0;
            offsetY = 1;
            break;
        case L:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX()+2, getLocationY());
            block4.setLocation(getLocationX(), getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(lightgrey);
            setWidth(3);
            setHeight(3); // Fudged
            offsetX = 0;
            offsetY = 1;
            break;
        case S:
            block1.setLocation(getLocationX()+1, getLocationY());
            block2.setLocation(getLocationX()+2, getLocationY());
            block3.setLocation(getLocationX(), getLocationY()+1);
            block4.setLocation(getLocationX()+1, getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(green);
            setWidth(3);
            setHeight(2);
            offsetX = 0;
            offsetY = 0;
            break;
        case Z:
            block1.setLocation(getLocationX(), getLocationY());
            block2.setLocation(getLocationX()+1, getLocationY());
            block3.setLocation(getLocationX()+1, getLocationY()+1);
            block4.setLocation(getLocationX()+2, getLocationY()+1);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(red);
            setWidth(3);
            setHeight(2);
            offsetX = 0;
            offsetY = 0;
            break;
    }
}












