/*
 * TetrominoBase.h
 *
 *  Created on: Apr 5, 2014
 *      Author: Austin
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
        TetrominoBase(GLUT_Plotter *g);
        TetrominoBase(GLUT_Plotter *g, int x, int y, int blockSize, int padding);
        TetrominoBase(const TetrominoBase&);
        TetrominoBase& operator =(const TetrominoBase&);
        
        virtual void initTetromino(TetrominoShape type) = 0;
        
        int offsetX;
        int offsetY;
};


#endif /* TETROMINOBASE_H_ */