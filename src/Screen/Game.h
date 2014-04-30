/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "Screen.h"
#include "PauseScreen.h"
#include "../PlayingField.h"
#include "../TetrominoBase.h"
#include "../Logo.h"
#include "../BlockString.h"

#include <cstdlib>
#include <ctime>
#include <mmsystem.h>

// Forward declaration of destination screens, due to potential for an inclusion loop
class PauseScreen;

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
        Screen* respondToKey(int) throw (EXIT);
        
        /*
         * Performs an action based on the passed Click.
         * 
         * Parameters:
         *   Click: The value of the Click to perform an action based upon
         *            
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen* respondToClick(Click) throw (EXIT);
        
        /*
         * Performs actions that should happen continuously in the background on this Screen.
         * 
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen* doBackground() throw (EXIT);
        
        /*
         * Sets Drawable member data width's, height's, and/or locations according to the size of
         *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
         *   the screen size changes.
         */
        void applyLayout();
        
        
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
         * Properly performs a shift up on currentTetromino, performing checks.
         */
        void doShiftUp();
        
        /*
         * Properly performs a shift down on currentTetromino, performing checks.
         */
        void doShiftDown();
        
        /*
         * Properly performs a shift left on currentTetromino, performing checks.
         */
        void doShiftLeft();
        
        /*
         * Properly performs a shift right on currentTetromino, performing checks.
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
         * Properly performs a clockwise rotation on currentTetromino, performing checks and wall
         *   kicks.
         */
        void doRotateCWWithKick();
        
        /*
         * Properly performs a counter-clockwise rotation on currentTetromino, performing checks
         *   and wall kicks.
         */
        void doRotateCCWWithKick();
        
        /*
         * Properly performs a soft fall on the currentTetromino, bringing it to the bottom of the
         *   screen without merging.
         */
        void doSoftFall();
        
        /*
         * Resets the currentTetromino and spawns a new one. Exists for testing purposes.
         */
        template <typename BlockType>
        void doResetTetromino();
        
        /*
         * Joins the currentTetromino with the field and spawns a new one.
         * 
         * Returns: True if a Tetromino could be successfully spawned, false otherwise

         */
        bool doJoinAndRespawn();
        
        /*
         * Used as a game "tick" marker for automatic tetromino falling, and the duration of the
         *   tick itself
         */
        clock_t prevTime;
        clock_t tick;
        
        /*
         * Represents the current score and level, which will be used to modify the duration of the
         *   tick and final score
         */
        int score;
        int level;
        
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
        
        /*
         * Game logo
         */
        Logo logo;
        
        BlockString scoreText;
        BlockString levelText;
        BlockString scoreNum;
        BlockString levelNum;
};


/* ---------- Method template implementation ---------- */

/*
 * Resets the currentTetromino and spawns a new one. Exists for testing purposes.
 */
template <typename BlockType>
void Game::doResetTetromino() {
    delete currentTetromino;
    delete shadow;
        
    // Spawn a new tetromino and create a shadow in the same place
    currentTetromino = field.spawnNewTetromino<BlockType>(currentTetromino->getShape());
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), 
            currentTetromino->getLocationY(), currentTetromino->getBlockSize(), 
            currentTetromino->getPadding(), currentTetromino->getShape(), field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    applyLayout();
    
    // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
    shadow->draw();
    currentTetromino->draw();
}

#endif /* GAMESCREEN_H_ */
