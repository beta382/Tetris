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
Screen(color),
        logo(0, 0, 25, 3, background),
        play(0, 0, 23, 0, "play", Color::BLACK, background),
        howToPlay(0, 0, 10, 0, "how to play", Color::BLACK, background),
        exit(0, 0, 10, 0, "exit", Color::BLACK, background),
        attribution(0, 0, 2, 0, 
                "created by: wes cossick, evan green, austin hash, and taylor jones", Color::GRAY,
                background)
{
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
Screen* MenuScreen::respondToKey(int key) throw (EXIT) {
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
Screen* MenuScreen::respondToClick(Click click) throw (EXIT) {
    // For now, just return to the previous screen
    Screen* nextScreen = NULL;
    
    if(click.x >= play.getLocationX() && 
            click.x < play.getLocationX()+play.getWidth() &&
        click.y >= play.getLocationY() && 
            click.y < play.getLocationY()+play.getHeight())
    {
        nextScreen = new Game(Color::TAN);
    } else if (
        click.x >= howToPlay.getLocationX() &&
            click.x < howToPlay.getLocationX()+howToPlay.getWidth() &&
        click.y >= howToPlay.getLocationY() && 
            click.y < howToPlay.getLocationY()+howToPlay.getHeight())
    {
        nextScreen = new InstructionScreen(Color::TAN);
    } else if (
        click.x >= exit.getLocationX() && click.x < exit.getLocationX()+exit.getWidth() &&
        click.y >= exit.getLocationY() && click.y < exit.getLocationY()+exit.getHeight())
    {
        throw EXIT();
    }
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* MenuScreen::doBackground() throw (EXIT) {
    Screen* nextScreen = NULL;
    
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= play.getLocationX() && 
            cursorX < play.getLocationX()+play.getWidth() &&
        cursorY >= play.getLocationY() && 
            cursorY < play.getLocationY()+play.getHeight())
    {
        play.setForeground(Color::GRAY);
    } else if (cursorX >= howToPlay.getLocationX() && 
            cursorX < howToPlay.getLocationX()+howToPlay.getWidth() &&
        cursorY >= howToPlay.getLocationY() && 
            cursorY < howToPlay.getLocationY()+howToPlay.getHeight())
    {
        howToPlay.setForeground(Color::GRAY);
    } else if (
        cursorX >= exit.getLocationX() && cursorX < exit.getLocationX()+exit.getWidth() &&
        cursorY >= exit.getLocationY() && cursorY < exit.getLocationY()+exit.getHeight())
    {
        exit.setForeground(Color::GRAY);
    } else {
        play.setForeground(Color::BLACK);
        howToPlay.setForeground(Color::BLACK);
        exit.setForeground(Color::BLACK);
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
    setWidth(g->getWidth());
    setHeight(g->getHeight());
    
    bgRect.setWidth(getWidth());
    bgRect.setHeight(getHeight());
    
    logo.setLocation((getWidth()-logo.getWidth())/2, getHeight()-logo.getHeight()-30);
    
    play.setLocation((getWidth()-play.getWidth())/2, logo.getLocationY()-play.getHeight()-60);
    
    howToPlay.setLocation((getWidth()-howToPlay.getWidth())/2, 
            play.getLocationY()-howToPlay.getHeight()-70);
    exit.setLocation((getWidth()-exit.getWidth())/2, howToPlay.getLocationY()-exit.getHeight()-30);
    
    attribution.setLocation((getWidth()-attribution.getWidth())/2, 10);
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void MenuScreen::draw() {
    bgRect.draw();
    logo.draw();
    play.draw();
    howToPlay.draw();
    exit.draw();
    attribution.draw();
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void MenuScreen::erase() {
    if (isVisible) {
        attribution.draw();
        exit.draw();
        howToPlay.draw();
        play.draw();
        logo.draw();
        bgRect.draw();
        
        
        isVisible = false;
    }
}
