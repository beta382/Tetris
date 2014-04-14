/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 13, 2014
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "Screen.h"
#include "PlayingField.h"
#include "TetrominoBase.h"
#include "blocks.h"

#include <cstdlib>
#include <ctime>

/*
 * Game:
 *
 * Inherits from Screen.
 *
 * Game is intended to represent the game screen, and be a wrapper for everything that the game
 *   screen contains. Game IS NOT intended to be inherited from.
 */

class Game: public Screen {
    public:
        Game(unsigned int color = Color::BLACK);
        ~Game();
        
        /* ---------- Implemented from Screen ---------- */
        Screen *respondToKey(int);
        Screen *respondToClick(Click);
        void doBackground();
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        
        /*
         * Prohibit copying or assignment
         */
        Game(const Game&);
        Game& operator =(const Game&);
        
        
        void init();
        
        void doRotateCW();
        void doRotateCCW();
        
        PlayingField *field;
        TetrominoBase *currentTetromino;
        Tetromino<GhostBlock> *shadow;
};


#endif /* GAMESCREEN_H_ */
