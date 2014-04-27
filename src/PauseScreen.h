/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef PAUSESCREEN_H_
#define PAUSESCREEN_H_

#include "Screen.h"
#include "Game.h"
#include "util.h"

/*
 * PauseScreen:
 *
 * Inherits from Screen.
 *
 * PauseScreen is intended to represent a paused screen, and be a wrapper for everything that the
 *   pause screen contains. PauseScreen IS NOT intended to be inherited from.
 */
class PauseScreen: public Screen {
_registerForLeakcheckWithID(PauseScreen)
    public:
        
        /*
         * Instantiates a PauseScreen object using the passed Screen* to return to.
         * 
         * Parameters:
         *   Screen* returnTo: A pointer to the screen object to return to
         */
        PauseScreen(Screen*);
        

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
         * 
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        Screen* doBackground();
        
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
         * Prevent default instantiation; we need to know where to return to.
         */
        PauseScreen();
        
        /*
         * Initializes this PauseScreen
         */
        void init();
        
        /*
         * The screen to return control to once this screen exits
         */
        Screen* returnTo;
        
        
        /* ---------- Implimented from Screen ---------- */
        
        /*
         * Sets Drawable member data width's, height's, and/or locations according to the size of
         *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
         *   the screen size changes.
         */
        void applyLayout();
};


#endif /* PAUSESCREEN_H_ */
