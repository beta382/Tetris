/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "Drawable.h"
#include "Shape.h"

enum TetrominoShape  {I, O, T, J, L, S, Z};

template <typename BlockType>
class Tetromino: public Shape {
    public:
        Tetromino(GLUT_Plotter *g);
        Tetromino(GLUT_Plotter *g, int x, int y, int blockSize, int padding, TetrominoShape shape);
        Tetromino(const Tetromino&);
        Tetromino& operator =(const Tetromino&);
        
        void rotateCW();
        void rotateCCW();
        
        int getOffsetX() const;
        int getOffsetY() const;
    private:
        void initTetromino(TetrominoShape type);
        
        int offsetX;
        int offsetY;
};

template <typename BlockType>
Tetromino<BlockType>::Tetromino(GLUT_Plotter *g): Shape(g) {
    initTetromino(S); // Picked by fair dice roll, guaranteed to be random
}

template <typename BlockType>
Tetromino<BlockType>::Tetromino (GLUT_Plotter *g, int x, int y, int blockSize, int padding, TetrominoShape shape): 
        Shape(g, x, y, blockSize, padding)
{
    initTetromino(shape);
}

template <typename BlockType>
Tetromino<BlockType>::Tetromino(const Tetromino<BlockType>& other): Shape(other) {
    offsetX = other.offsetX;
    offsetY = other.offsetY;
}

template <typename BlockType>
Tetromino<BlockType>& Tetromino<BlockType>::operator =(const Tetromino<BlockType>& rhs) {
    if (this != &rhs) {
        Shape::operator =(rhs);
        offsetX = rhs.offsetX;
        offsetY = rhs.offsetY;
    }
    
    return *this;
}

template <typename BlockType>
void Tetromino<BlockType>::rotateCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation(((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-getOffsetY()-
                  getOffsetX())*blocks[i]->getTotalSize()+getLocationX(),
                (getWidth()-((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+getOffsetX())-1+
                  getOffsetY())*blocks[i]->getTotalSize()+getLocationY());
    }
    draw();
    swap(width, height);
}

template <typename BlockType>
void Tetromino<BlockType>::rotateCCW() {
    erase();
    for (int i = 0; i < blocks.getSize(); i++) {
        blocks[i]->setLocation((getHeight()-((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-
                  getOffsetY())-1-getOffsetX())*blocks[i]->getTotalSize()+getLocationX(),
                ((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+getOffsetX()+getOffsetY())*
                  blocks[i]->getTotalSize()+getLocationY());
    }
    draw();
    swap(width, height);
}

template <typename BlockType>
int Tetromino<BlockType>::getOffsetX() const {
    return offsetX;
}

template <typename BlockType>
int Tetromino<BlockType>::getOffsetY() const {
    return offsetY;
}

template <typename BlockType>
void Tetromino<BlockType>::initTetromino (TetrominoShape type) {
    Block *block1, *block2, *block3, *block4;
    
    offsetX = 0;
    offsetY = 0;
    
    // Some heights/widths are "fudged", so that this fake bounding rectangle can apply desired rotations.
    switch (type) {
        case I:
            block1 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize()*4, 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize()*4, 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize()*4, 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize()*3, getLocationY()+getTotalBlockSize()*4, 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::CYAN);
            setWidth(4);
            setHeight(5); // Fudged
            offsetY = 2;
            break;
        case O:
            block1 = new BlockType(g, getLocationX(), getLocationY(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY(), 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::YELLOW);
            setWidth(2);
            setHeight(2);
            break;
        case T:
            block1 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::MAGENTA);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case J:
            block1 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::BLUE);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case L:
            block1 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize()*2, 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::ORANGE);
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case S:
            block1 = new BlockType(g, getLocationX(), getLocationY(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY(), 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::GREEN);
            setWidth(3);
            setHeight(2);
            break;
        case Z:
            block1 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY(), 
                    getBlockSize(), getPadding());
            block2 = new BlockType(g, getLocationX()+getTotalBlockSize()*2, getLocationY(), 
                    getBlockSize(), getPadding());
            block3 = new BlockType(g, getLocationX(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            block4 = new BlockType(g, getLocationX()+getTotalBlockSize(), getLocationY()+getTotalBlockSize(), 
                    getBlockSize(), getPadding());
            
            blocks.pushBack(block1).pushBack(block2).pushBack(block3).pushBack(block4);
            
            setColor(Color::RED);
            setWidth(3);
            setHeight(2);
            break;
    }
}


#endif /* TETROMINO_H_ */
