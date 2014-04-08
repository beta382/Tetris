/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "Drawable.h"
#include "PlayingField.h"
#include "TetrominoBase.h"
#include "Blocks.h" // In turn includes all of our special blocks
#include "Rectangle.h"

#include <cstdlib>
#include <ctime>

/*
 * Game:
 *
 * Inherits from Drawable.
 *
 * Game is intended to represent the game screen, and be a wrapper for everything that the game screen contains. Game is
 *   not intended to be inherited from.
 *
 * Member data:
 *     `PlayingField *field`: Pointer to a PlayingField object representing the main gameplay area.
 *     `TetrominoBase *currentTetromino`: Pointer to a TetrominoBase object (which can be any Tetromino<BlockType>)
 *       representing the currently falling tetromino.
 *
 * Public functions:
 *     `void respondToKey(int)`: Performs a gameplay action based on the pressed key.
 *
 * Private functions:
 *     `void init()`: Initializes member data and the RNG.
 *
 * Functions inherited from Drawable:
 *     `void draw()`
 *     `void erase()`
 */

// TODO: Maybe eventually subclass Drawable into a Screen object, and then make the game-screen, menu-screen, etc.
// all inherit from that. Would allow for a polymorphic Screen pointer in the Tetris class.

class Game: public Drawable {
    public:
        Game(GLUT_Plotter *g);
        ~Game();
        
        void respondToKey(int key);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        void init();
        
        PlayingField *field;
        TetrominoBase *currentTetromino;
};


#endif /* GAMESCREEN_H_ */
