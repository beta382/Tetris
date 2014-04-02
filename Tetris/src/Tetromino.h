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

class Tetromino: public Shape {
    public:
        Tetromino(GLUT_Plotter *g);
        Tetromino(GLUT_Plotter *g, int x, int y, TetrominoShape type);
        
        void rotateCW();
        void rotateCCW();
        
        int getOffsetX() const;
        int getOffsetY() const;
    private:
        void initTetromino(TetrominoShape type);
        
        int offsetX;
        int offsetY;
};

#endif /* TETROMINO_H_ */
