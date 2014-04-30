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
    
    if(click.x >= play.getLocationX() && 
            click.x < play.getLocationX()+play.getWidth() &&
        click.y >= play.getLocationY() && 
            click.y < play.getLocationY()+play.getHeight()
       && !howToPlayVisible)
    {
        nextScreen = new Game(Color::TAN);
    }
    else if(
        click.x >= howToPlay.getLocationX() && 
            click.x < howToPlay.getLocationX()+howToPlay.getWidth() &&
        click.y >= howToPlay.getLocationY() && 
            click.y < howToPlay.getLocationY()+howToPlay.getHeight())
    {
        howToPlayVisible = true;
    }
    else if(click.x >= 0 && click.x < 100
       && click.y >= 355 && click.y < 400)
    {
        howToPlayVisible = false;
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
    
    if (cursorX >= play.getLocationX() && 
            cursorX < play.getLocationX()+play.getWidth() &&
        cursorY >= play.getLocationY() && 
            cursorY < play.getLocationY()+play.getHeight())
    {
        play.setFileName("img/Play Hover.bmp");
    }
    else
    {
        play.setFileName("img/Play.bmp");
    }
    
    if (cursorX >= howToPlay.getLocationX() && 
            cursorX < howToPlay.getLocationX()+howToPlay.getWidth() &&
        cursorY >= howToPlay.getLocationY() && 
            cursorY < howToPlay.getLocationY()+howToPlay.getHeight())
    {
        howToPlay.setFileName("img/How To Play Hover.bmp");
    }
    else
    {
        howToPlay.setFileName("img/How To Play.bmp");
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
    
    if(howToPlayVisible)
        howToPlayImage.draw();
    else
        howToPlayImage.erase();
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
    logo.setFileName("img/logo_large.bmp");
    play.setFileName("img/Play.bmp");
    howToPlay.setFileName("img/How To Play.bmp");
    attribution.setFileName("img/Attribution.bmp");
    howToPlayImage.setFileName("img/How to Play Screen.bmp");

    logo.setLocation(25, 300);
    play.setLocation(150, 180);
    howToPlay.setLocation(8, 100);
    attribution.setLocation(25, 5);
    howToPlayImage.setLocation(0, 0);
}
