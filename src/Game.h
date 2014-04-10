/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 10, 2014
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "Screen.h"
#include "PlayingField.h"
#include "TetrominoBase.h"
#include "Blocks.h" // In turn includes all of our special blocks
#include "Rectangle.h"

#include <cstdlib>
#include <ctime>

/*
 * Game:
 *
 * Inherits from Screen.
 *
 * Game is intended to represent the game screen, and be a wrapper for everything that the game screen contains. Game IS
 *   NOT intended to be inherited from.
 *
 * Constructors:
 *     `Game()`: Calls `Screen()`, then calls `void init()`.
 *
 * Private member data:
 *     `PlayingField *field`: Pointer to a PlayingField object representing the main gameplay area.
 *     `TetrominoBase *currentTetromino`: Pointer to a TetrominoBase object (which can be any Tetromino<BlockType>)
 *       representing the currently falling tetromino.
 *     `Tetromino<GhostBlock> *shadow`: Pointer to a Tetromino<GhostBlock> object representing the final location of the
 *       currently falling tetromino should it be allowed to fall all the way to the bottom without shifting left or
 *       right.
 *
 * Public functions:
 *     `void respondToKey(int)`: Performs a gameplay action based on the pressed key.
 *
 * Private functions:
 *     `void init()`: Initializes member data and the RNG, draws the initial state to the screen.
 *
 * Functions implemented from Drawable:
 *     `void draw()`
 *     `void erase()`
 */

class Game: public Screen {
    public:
        Game();
        ~Game();
        
        /* ---------- Implemented from Screen ---------- */
        void respondToKey(int);
        void respondToClick(Click);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        void init();
        
        void doRotateCW();
        void doRotateCCW();
        
        PlayingField *field;
        TetrominoBase *currentTetromino;
        Tetromino<GhostBlock> *shadow;
};


#endif /* GAMESCREEN_H_ */
