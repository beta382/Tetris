/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 15, 2014
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
        
        /*
         * Instantiates a Game object using the passed foreground color or default values.
         * 
         * Parameters:
         *   unsigned int color: The value to initialize this Game object's foreground with,
         *     defaults to Color::BLACK
         */
        Game(unsigned int color = Color::BLACK);

        /*
         * Destructs this Game object.
         */
        ~Game();
        
        
        /* ---------- Implemented from Screen ---------- */
        
        /*
         * Performs an action based on the passed key.
         * 
         * Parameters:
         *   int key: The value of the key to perform an action based upon
         *   
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen *respondToKey(int);
        
        /*
         * Performs an action based on the passed Click.
         * 
         * Parameters:
         *   Click: The value of the Click to perform an action based upon
         *            
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen *respondToClick(Click);
        
        /*
         * Performs actions that should happen continuously in the background on this Screen.
         */
        void doBackground();
        
        
        /* ---------- Implemented from Drawable ---------- */
        
        /*
         * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
         */
        void draw();
        
        /*
         * Erases all Drawable member data from the screen in an order that preserves view
         *   heiarchy.
         */
        void erase();
    private:
        
        /*
         * Prohibit copying or assignment
         */
        Game(const Game&);
        Game& operator =(const Game&);
        
        /*
         * Instantiates this Game object's dynamically allocated member data and starts the RNG.
         */
        void init();
        
        /*
         * Properly performs a clockwise rotation on currentTetromino WITHOUT performing checks.
         */
        void doRotateCW();
        
        /*
         * Properly performs a counter-clockwise rotation on currentTetromino WITHOUT performing
         *   checks.
         */
        void doRotateCCW();
        
        /*
         * PlayingField object that represents the area of main gameplay.
         */
        PlayingField field;
        
        /*
         * Pointer to a TetrominoBase object representing the currently falling tetromino.
         */
        TetrominoBase *currentTetromino;
        
        /*
         * Pointer to a Tetromino<GhostBlock> object representing the currently falling tetromino's
         *   shadow.
         */
        Tetromino<GhostBlock> *shadow;
};


#endif /* GAMESCREEN_H_ */
