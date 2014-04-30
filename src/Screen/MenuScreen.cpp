/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */


#include "MenuScreen.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a MenuScreen object using the passed Screen* to return to.
 * 
 * Parameters:
 *   Game* return: A pointer to the screen object to return to
 */
MenuScreen::MenuScreen(unsigned int color):
Screen(color)
{
    init();
}

/*
 * Destructs this MenuScreen object.
 */
MenuScreen::~MenuScreen() {
    erase();
}


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
Screen* MenuScreen::respondToKey(int key) {
    Screen* nextScreen = NULL;
    
    return nextScreen;
}

/*
 * Performs an action based on the passed Click.
 * 
 * Parameters:
 *   Click: The value of the Click to perform an action based upon
 *            
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* MenuScreen::respondToClick(Click click) {
    // For now, just return to the previous screen
    Screen* nextScreen = NULL;
    
    if(true)
    {
        nextScreen = NULL;
    }
    else
    {
        nextScreen = new Game(Color::TAN);
    }
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* MenuScreen::doBackground() {
    Screen* nextScreen = NULL;
    
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (true)
    {
        // Cursor goes here
    }
    else
    {
        
    }
    
    applyLayout();
    draw();
    
    return nextScreen;
}

/*
 * Sets Drawable member data width's, height's, and/or locations according to the size of
 *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
 *   the screen size changes.
 */
void MenuScreen::applyLayout() {
    // Can be updated later
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void MenuScreen::draw() {
    isVisible = true;
    
    bgRect.draw();
    logo.draw();
    play.draw();
    howToPlay.draw();
    attribution.draw();
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void MenuScreen::erase() {
    if (isVisible) {
        isVisible = false;
    }
}


/* ---------- Private ---------- */

/*
 * Initializes this MenuScreen
 */
void MenuScreen::init() {
    logo.setFileName("../img/logo_large.bmp");
    play.setFileName("../img/Play.bmp");
    playHover.setFileName("../img/Play Hover.bmp");
    howToPlay.setFileName("../img/How To Play.bmp");
    howToPlayHover.setFileName("../img/How To Play Hover.bmp");
    attribution.setFileName("../img/Attribution.bmp");
    /* Will set when ready
    logo.setLocation();
    play.setLocation();
    playHover.setLocation();
    howToPlay.setLocation();
    howToPlayHover.setLocation();
    attribution.setLocation();
    */    
}
