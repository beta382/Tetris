/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "PauseScreen.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a PauseScreen object using the passed Screen* to return to.
 * 
 * Parameters:
 *   Game* bgGame: A pointer to the screen object to return to
 */
PauseScreen::PauseScreen(Game* bgGame):
Screen(),
        bgGame(bgGame), resumeText(0, 0, 16, 2, "resume"), 
        exitText(0, 0, 16, 2, "exit")
{
}

/*
 * Destructs this PauseScreen object.
 */
PauseScreen::~PauseScreen() {
    erase();
    delete bgGame;
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
Screen* PauseScreen::respondToKey(int key) throw (EXIT) {
    Screen* nextScreen = NULL;
    
    switch (key) {
        case 'p':
        case ' ':
            nextScreen = bgGame;
            bgGame = NULL;
            break;
        case 'e':
        case Key::ESC:
            nextScreen = new MenuScreen(Color::TAN);
            delete bgGame;
            bgGame = NULL;
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
Screen* PauseScreen::respondToClick(Click click) throw (EXIT) {
    // For now, just return to the previous screen
    Screen* nextScreen = NULL;
    
    if (click.x >= resumeText.getLocationX() && 
            click.x < resumeText.getLocationX()+resumeText.getWidth() &&
        click.y >= resumeText.getLocationY() && 
            click.y < resumeText.getLocationY()+resumeText.getHeight())
    {
        nextScreen = bgGame;
        bgGame = NULL;
    } else if (
        click.x >= exitText.getLocationX() && 
            click.x < exitText.getLocationX()+exitText.getWidth() &&
        click.y >= exitText.getLocationY() && 
            click.y < exitText.getLocationY()+exitText.getHeight())
    {
        nextScreen = new MenuScreen(Color::TAN);
        delete bgGame;
        bgGame = NULL;
    }
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
Screen* PauseScreen::doBackground() throw (EXIT) {
    Screen* nextScreen = NULL;
    
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= resumeText.getLocationX() && 
            cursorX < resumeText.getLocationX()+resumeText.getWidth() &&
        cursorY >= resumeText.getLocationY() && 
            cursorY < resumeText.getLocationY()+resumeText.getHeight())
    {
        resumeText.setForeground(Color::REAL_GREEN);
        exitText.setForeground(Color::RED);
    } else if (
        cursorX >= exitText.getLocationX() && 
            cursorX < exitText.getLocationX()+exitText.getWidth() &&
        cursorY >= exitText.getLocationY() && 
            cursorY < exitText.getLocationY()+exitText.getHeight())
    {
        exitText.setForeground(Color::DARK_RED);
        resumeText.setForeground(Color::GREEN);
    } else {
        resumeText.setForeground(Color::GREEN);
        exitText.setForeground(Color::RED);
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
void PauseScreen::applyLayout() {
    resumeText.setLocation(g->getWidth()/2-resumeText.getWidth()/2, g->getHeight()/2+30);
    exitText.setLocation(g->getWidth()/2-exitText.getWidth()/2, g->getHeight()/2
            -exitText.getHeight()-30);
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void PauseScreen::draw() {
    isVisible = true;
    
    if (bgGame) {
        bgGame->applyLayout();
        bgGame->draw();
    }
    
    char* sharedPixelBuffer = g->getBuffer();
    
    // Darkens the screen
    for (int i = 0; i < g->getBufferLen(); i++) {
        sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/4;
    }
    
    
    resumeText.draw();
    exitText.draw();
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void PauseScreen::erase() {
    if (isVisible) {
        exitText.erase();
        resumeText.erase();
        
        if (bgGame) {
            bgGame->erase();
        }
        
        isVisible = false;
    }
}
