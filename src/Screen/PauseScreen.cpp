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
 *   Game* bgScreen: A pointer to the screen object to return to
 */
PauseScreen::PauseScreen(GameScreen* bgScreen):
Screen(),
        bgScreen(bgScreen), title(0, 0, 20, 0, "paused", Color::LIGHT_GRAY),
        resume(0, 0, 12, 0, "resume game", Color::GREEN), 
        exit(0, 0, 12, 0, "exit to menu", Color::RED)
{
}

/*
 * Destructs this PauseScreen object.
 */
PauseScreen::~PauseScreen() {
    erase();
    delete bgScreen;
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
void PauseScreen::respondToKey(int key) throw (QUIT, NEW_SCREEN) {
    switch (key) {
        case 'p':
        case ' ':
            PSdoResume();
            break;
        case 'e':
        case Key::ESC:
            PSdoExit();
            break;
    }
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
void PauseScreen::respondToClick(Click click) throw (QUIT, NEW_SCREEN) {
    if (click.button == GLUT_LEFT_BUTTON && click.state == GLUT_UP) {
        if (click.x >= resume.getLocationX() && 
                click.x < resume.getLocationX()+resume.getWidth() &&
            click.y >= resume.getLocationY() && 
                click.y < resume.getLocationY()+resume.getHeight())
        {
            PSdoResume();
        } else if (
            click.x >= exit.getLocationX() && click.x < exit.getLocationX()+exit.getWidth() &&
            click.y >= exit.getLocationY() && click.y < exit.getLocationY()+exit.getHeight())
        {
            PSdoExit();
        }
    }
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function
 *   exits, or NULL if control should not shift to another Screen object
 */
void PauseScreen::doBackground() throw (QUIT, NEW_SCREEN) {
    // If we previously retained this and returned, stop saying to retain or we'll leak
    if (retain) {
        retain = false;
    }
    
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= resume.getLocationX() && 
            cursorX < resume.getLocationX()+resume.getWidth() &&
        cursorY >= resume.getLocationY() && 
            cursorY < resume.getLocationY()+resume.getHeight())
    {
        resume.setForeground(Color::REAL_GREEN);
        exit.setForeground(Color::RED);
    } else if (
        cursorX >= exit.getLocationX() && 
            cursorX < exit.getLocationX()+exit.getWidth() &&
        cursorY >= exit.getLocationY() && 
            cursorY < exit.getLocationY()+exit.getHeight())
    {
        exit.setForeground(Color::DARK_RED);
        resume.setForeground(Color::GREEN);
    } else {
        resume.setForeground(Color::GREEN);
        exit.setForeground(Color::RED);
    }
    
    applyLayout();
    draw();
}

/*
 * Sets Drawable member data width's, height's, and/or locations according to the size of
 *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
 *   the screen size changes.
 */
void PauseScreen::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());
    
    title.setLocation((getWidth()-title.getWidth())/2, getHeight()-title.getHeight()-30);
    
    resume.setLocation((g->getWidth()-resume.getWidth())/2,
            g->getHeight()/2+resume.getTotalBlockSize()*2);
    exit.setLocation((g->getWidth()-exit.getWidth())/2,
            resume.getLocationY()-exit.getHeight()-exit.getTotalBlockSize()*4);
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void PauseScreen::draw() {
    if (bgScreen) {
        bgScreen->applyLayout();
        bgScreen->draw();
    }
    
    if (!retain) {
        char* sharedPixelBuffer = g->getBuffer();
        
        // Darkens the screen
        for (int i = 0; i < g->getBufferLen(); i++) {
            sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/8;
        }
        
        title.draw();
        
        resume.draw();
        exit.draw();
        
        isVisible = true;
    }
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void PauseScreen::erase() {
    if (isVisible) {
        exit.erase();
        resume.erase();
        title.erase();
        
        if (bgScreen) {
            bgScreen->erase();
        }
        
        isVisible = false;
    }
}
