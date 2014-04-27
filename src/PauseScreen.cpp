/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "PauseScreen.h"

/*
 * Instantiates a PauseScreen object using the passed Screen* to return to.
 * 
 * Parameters:
 *   Screen* return: A pointer to the screen object to return to
 */
PauseScreen::PauseScreen(Screen* returnTo):
Screen(),
        returnTo(returnTo)
{
    init();
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
Screen* PauseScreen::respondToKey(int key) {
    Screen* nextScreen = NULL;
    
    switch (key) {
        case 'p':
            nextScreen = returnTo;
            break;
        case 'n':
            nextScreen = new Game(Color::TAN);
            delete returnTo;
            break;
    }
    
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
Screen* PauseScreen::respondToClick(Click click) {
    // For now, just return to the previous screen
    Screen* nextScreen = returnTo;
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* PauseScreen::doBackground() {
    Screen* nextScreen = NULL;
    
    draw();
    
    return nextScreen;
}

/*
 * Sets Drawable member data width's, height's, and/or locations according to the size of
 *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
 *   the screen size changes.
 */
void PauseScreen::applyLayout() {
    // Do nothing
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void PauseScreen::draw() {
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view
 *   heiarchy.
 */
void PauseScreen::erase() {
    if (isVisible) {
        
        isVisible = false;
    }
}


/* ---------- Private ---------- */

/*
 * Initializes this PauseScreen
 */
void PauseScreen::init() {
    applyLayout();

    char* sharedPixelBuffer = g->getBuffer();
    
    // Darkens the screen
    for (int i = 0; i < g->getBufferLen(); i++) {
        sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/2;
    }
}
