/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */


#include "HowToPlay.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a HowToPlay object using the passed Screen* to return to.
 * 
 * Parameters:
 *   Game* return: A pointer to the screen object to return to
 */
HowToPlay::HowToPlay(unsigned int color):
Screen(color)
{
    init();
}

/*
 * Destructs this HowToPlay object.
 */
HowToPlay::~HowToPlay() {
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
Screen* HowToPlay::respondToKey(int key) {
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
Screen* HowToPlay::respondToClick(Click click) {
    // For now, just return to the previous screen
    Screen* nextScreen = NULL;
    
    if(click.x >= 0 && click.x < 100
       && click.y >= 355 && click.y < 400)
    {
        nextScreen = new MenuScreen(Color::TAN);
    }
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* HowToPlay::doBackground() {
    Screen* nextScreen = NULL;
    
    applyLayout();
    draw();
    
    return nextScreen;
}

/*
 * Sets Drawable member data width's, height's, and/or locations according to the size of
 *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
 *   the screen size changes.
 */
void HowToPlay::applyLayout() {
    // Can be updated later
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void HowToPlay::draw() {
    isVisible = true;
    
    howToPlayImage.draw();
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void HowToPlay::erase() {
    if (isVisible) {
        isVisible = false;
    }
}


/* ---------- Private ---------- */

/*
 * Initializes this HowToPlay
 */
void HowToPlay::init() {
    howToPlayImage.setFileName("Tetris/img/How to Play Screen.bmp");

    howToPlayImage.setLocation(0, 0);
}
