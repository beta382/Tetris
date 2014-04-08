/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  5, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef TETROMINOBASE_H_
#define TETROMINOBASE_H_

#include "Shape.h"

enum TetrominoShape  {I, O, T, J, L, S, Z};

// Provides a specialized base class for all possible Tetromino<type> classes
class TetrominoBase: public Shape {
    public:
        void rotateCW();
        void rotateCCW();
        
        int getOffsetX() const;
        int getOffsetY() const;
    protected:
        TetrominoBase();
        TetrominoBase(int x, int y, int blockSize, int padding,
                unsigned int background = Color::BLACK);
        TetrominoBase(const TetrominoBase&);
        TetrominoBase& operator =(const TetrominoBase&);
        
        virtual void initTetromino(TetrominoShape type) = 0;
        
        int offsetX;
        int offsetY;
};


#endif /* TETROMINOBASE_H_ */
