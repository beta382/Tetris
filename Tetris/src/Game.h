/*
 * Game.h
 *
 *  Created on: Apr 3, 2014
 *      Author: Austin
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "Drawable.h"
#include "PlayingField.h"
#include "Tetromino.h"

#include <cstdlib>
#include <ctime>

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
        Tetromino<Block> *currentTetromino;
};


#endif /* GAMESCREEN_H_ */
