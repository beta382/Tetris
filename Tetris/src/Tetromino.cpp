/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "Tetromino.h"

Tetromino::Tetromino(GLUT_Plotter *g): Shape(g) {
    initTetromino(S); // Picked by fair dice roll, guaranteed to be random
}

Tetromino::Tetromino (GLUT_Plotter *g, int x, int y, TetrominoShape type): Shape(g, x, y) {
    initTetromino(type);
}

// TODO: Make these work with arbitrarily sized Blocks
void Tetromino::rotateCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation((blocks[i]->getLocationY()-getLocationY()-offsetY)+getLocationX()-offsetX,
                getWidth()-(blocks[i]->getLocationX()-getLocationX()+offsetX)-1+getLocationY()+offsetY);
    }
    draw();
    swap(width, height);
}

void Tetromino::rotateCCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation(getHeight()-(blocks[i]->getLocationY()-getLocationY()-offsetY)-1+getLocationX()-offsetX,
                (blocks[i]->getLocationX()-getLocationX()+offsetX)+getLocationY()+offsetY);
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
    Block *block1, *block2, *block3, *block4;
    
    offsetX = 0;
    offsetY = 0;
    
    // Some heights/widths are "fudged", so that this fake bounding rectangle can apply desired rotations.
    switch (type) {
        case I:
            block1 = new Block(g, getLocationX(), getLocationY()+4*BLOCK_SIZE, BLOCK_SIZE);
            block2 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+4*BLOCK_SIZE, BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+4*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+3*BLOCK_SIZE, getLocationY()+4*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::CYAN);
            setWidth(4);
            setHeight(5); // Fudged
            offsetY = 2;
            break;
        case O:
            block1 = new Block(g, getLocationX(), getLocationY(), BLOCK_SIZE);
            block2 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY(), BLOCK_SIZE);
            block3 = new Block(g, getLocationX(), getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::YELLOW);
            setWidth(2);
            setHeight(2);
            break;
        case T:
            block1 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block2 = new Block(g, getLocationX(), getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::MAGENTA);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case J:
            block1 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block2 = new Block(g, getLocationX(), getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::BLUE);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case L:
            block1 = new Block(g, getLocationX(), getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block2 = new Block(g, getLocationX(), getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+2*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::ORANGE);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case S:
            block1 = new Block(g, getLocationX(), getLocationY(), BLOCK_SIZE);
            block2 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY(), BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::GREEN);
            setWidth(3);
            setHeight(2);
            break;
        case Z:
            block1 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY(), BLOCK_SIZE);
            block2 = new Block(g, getLocationX()+2*BLOCK_SIZE, getLocationY(), BLOCK_SIZE);
            block3 = new Block(g, getLocationX()+0, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            block4 = new Block(g, getLocationX()+1*BLOCK_SIZE, getLocationY()+1*BLOCK_SIZE, BLOCK_SIZE);
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::RED);
            setWidth(3);
            setHeight(2);
            break;
    }
}












