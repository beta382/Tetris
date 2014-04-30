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
#include "Game.h"
#include "../Image.h"

class Game; // Needed because of the circular inclusion

/*
 * MenuScreen:
 *
 * Inherits from Screen.
 *
 * MenuScreen is intended to represent a paused screen, and be a wrapper for everything that the
 *   pause screen contains. MenuScreen IS NOT intended to be inherited from.
 */
class MenuScreen: public Screen {
_registerForLeakcheckWithID(MenuScreen)
    public:
        
        /*
         * Instantiates a MenuScreen object using the passed Games* to return to.
         * 
         * Parameters:
         *   Game* background: A pointer to the screen object to return to
         */
        MenuScreen(unsigned int color = Color::BLACK);
        
        /*
         * Destructs this MenuScreen object.
         */
        ~MenuScreen();
        

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
         * Initializes this MenuScreen
         */
        void init();
        
        
        // Images for elements of menu screen
        Image logo;
        Image attribution;
        Image play;
        Image playHover;
        Image howToPlay;
        Image howToPlayHover;
        Image howToPlayImage;
        
        // Boolean for whether how to play is visible
        bool howToPlayVisible;
};

#endif // MENUSCREEN_H_INCLUDED
