/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */

#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include "Screen.h"
#include "MenuScreen.h"
#include "../Image.h"


/*
 * HowToPlay:
 *
 * Inherits from Screen.
 *
 * HowToPlay is intended to represent a paused screen, and be a wrapper for everything that the
 *   pause screen contains. HowToPlay IS NOT intended to be inherited from.
 */
class HowToPlay: public Screen {
_registerForLeakcheckWithID(HowToPlay)
    public:
        
        /*
         * Instantiates a HowToPlay object using the passed Games* to return to.
         * 
         * Parameters:
         *   Game* background: A pointer to the screen object to return to
         */
        HowToPlay(unsigned int color = Color::BLACK);
        
        /*
         * Destructs this HowToPlay object.
         */
        ~HowToPlay();
        

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
         * Initializes this HowToPlay
         */
        void init();
        
        
        // Images for elements of menu screen
        Image howToPlayImage;
};

#endif // MENUSCREEN_H_INCLUDED
