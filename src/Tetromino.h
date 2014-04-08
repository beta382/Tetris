/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "TetrominoBase.h"

template <typename BlockType>
class Tetromino: public TetrominoBase {
    public:
        Tetromino(GLUT_Plotter *g);
        Tetromino(GLUT_Plotter *g, int x, int y, int blockSize, int padding, TetrominoShape shape, 
                unsigned int background = Color::BLACK);
        Tetromino(const Tetromino<BlockType>&);
        Tetromino<BlockType>& operator =(const Tetromino<BlockType>&);
    private:
        /* ---------- Implemented from TetrominoBase ---------- */
        void initTetromino(TetrominoShape type);
};


/* ---------- Tetromino class template implementation ---------- */

template <typename BlockType>
Tetromino<BlockType>::Tetromino(GLUT_Plotter *g): TetrominoBase(g) {
    initTetromino(S); // Picked by fair dice roll, guaranteed to be random
}

template <typename BlockType>
Tetromino<BlockType>::Tetromino (GLUT_Plotter *g, int x, int y, int blockSize, int padding, TetrominoShape shape,
        unsigned int background): TetrominoBase(g, x, y, blockSize, padding, background)
{
    initTetromino(shape);
}

template <typename BlockType>
Tetromino<BlockType>::Tetromino(const Tetromino<BlockType>& other): TetrominoBase(other) {}

template <typename BlockType>
Tetromino<BlockType>& Tetromino<BlockType>::operator =(const Tetromino<BlockType>& rhs) {
    if (this != &rhs) {
        TetrominoBase::operator =(rhs);
    }
    
    return *this;
}

template <typename BlockType>
void Tetromino<BlockType>::initTetromino (TetrominoShape type) {
    Block *block1, *block2, *block3, *block4;
    
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::BLUE);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::GREEN);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::BROWN);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::GRAY);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::RED);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::DARK_GREEN);
            setBackground(getBackground());
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
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::CYAN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(2);
            break;
    }
}


#endif /* TETROMINO_H_ */
