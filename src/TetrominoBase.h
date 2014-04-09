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

/*
 * TetrominoShape:
 *
 * Enumeration of all possible shapes a TetrominoBase may take.
 */

enum TetrominoShape  {I, O, T, J, L, S, Z};

/*
 * TetrominoBase:
 *
 * Inherits from Shape.
 *
 * TetrominoBase is intended to be the abstract base class for all possible Tetromino<BlockType> classes. You MAY NOT
 *   independantly instantiate a TetrominoBase object, this is enforced by making the constructors protected.
 *
 * Constructors:
 *     `TetrominoBase()`: Calls `Shape()` and initializes `int offsetX` and `int offsetY` to 0.
 *     `TetrominoBase(int x, int y, int blockSize, int padding, unsigned int background)`: Calls
 *       `Shape(x, y, blockSize, padding, background)` and initializes `int offsetX` and `int offsetY` to the passed
 *       values.
 *
 * Protected member data:
 *     `int offsetX`/`int offsetY`: Used to alter rotation behavior of a TetrominoBase. Specifically, describes how to
 *       shift the bounding rectangle prior to rotating the TetrominoBase.
 *
 * Public functions:
 *     `void rotateCW()`/`void rotateCCW()`: Rotates the TetrominoBase one quarter rotation in the respective direction,
 *       without performing checks. Within the context of a PlayingField, should be surrounded with a conditional.
 *     `int getOffsetX()`/`int getOffsetY()`: Getters for `int offsetX` and `int offsetY`.
 *
 * Protected functions:
 *     `void initTetromino(TetrominoShape)`: Pure virtual function that MUST be implemented by descendants of
 *       TetrominoBase to initialize the tetromino with the specified shape.
 *
 * All objects that directly inherit from TetrominoBase MUST:
 *     Implement `void initTetromino(TetrominoShape)`
 */

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
