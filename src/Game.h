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
#include "util.h"

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
_registerForLeakcheckWithID(Game)
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
        Screen* respondToKey(int);
        
        /*
         * Performs an action based on the passed Click.
         * 
         * Parameters:
         *   Click: The value of the Click to perform an action based upon
         *            
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen* respondToClick(Click);
        
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
         * Properly performs a shift up on currentTetromino WITHOUT performing checks.
         */
        void doShiftUp();
        
        /*
         * Properly performs a shift down on currentTetromino WITHOUT performing checks.
         */
        void doShiftDown();
        
        /*
         * Properly performs a shift left on currentTetromino WITHOUT performing checks.
         */
        void doShiftLeft();
        
        /*
         * Properly performs a shift right on currentTetromino WITHOUT performing checks.
         */
        void doShiftRight();
        
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
         * Resets the currentTetromino and spawns a new one. Exists for testing purposes.
         */
        template <typename BlockType>
        void doResetTetromino();
        
        /*
         * Joins the currentTetromino with the field and spawns a new one.
         */
        void doJoinAndRespawn();
        
        /*
         * PlayingField object that represents the area of main gameplay.
         */
        PlayingField field;
        
        /*
         * Pointer to a TetrominoBase object representing the currently falling tetromino.
         */
        TetrominoBase* currentTetromino;
        
        /*
         * Pointer to a TetrominoBase object representing the currently falling tetromino.
         */
        TetrominoBase* tetrominoNext;
        
        /*
         * Pointer to a Tetromino<GhostBlock> object representing the currently falling tetromino's
         *   shadow.
         */
        Tetromino<GhostBlock>* shadow;
        
        /*
         * Background rectangle for next block
         */
        MyRectangle bgRectNext;
        
        /*
         * Background rectangle border for next block
         */
        MyRectangle bgRectNext2;
};


/* ---------- Method template implementation ---------- */

/*
 * Resets the currentTetromino and spawns a new one. Exists for testing purposes.
 */
template <typename BlockType>
void Game::doResetTetromino() {
    delete currentTetromino;
    delete shadow;
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7);
        
    // Spawn a new tetromino and create a shadow in the same place
    currentTetromino = field.spawnNewTetromino<BlockType>(shape, tetrominoNext);
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
            currentTetromino->getBlockSize(), currentTetromino->getPadding(), currentTetromino->getShape(),
            field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
    shadow->draw();
    currentTetromino->draw();
}

#endif /* GAMESCREEN_H_ */
