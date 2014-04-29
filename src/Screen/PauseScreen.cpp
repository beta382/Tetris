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
 *   Game* return: A pointer to the screen object to return to
 */
PauseScreen::PauseScreen(Game* background):
Screen(),
        background(background), resumeText(0, 0, 16, 2), exitText(0, 0, 16, 2)
{
    init();
}

/*
 * Destructs this PauseScreen object.
 */
PauseScreen::~PauseScreen() {
    erase();
    delete background;
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
        case 'r':
        case 'p':
        case ' ':
            nextScreen = background;
            background = NULL;
            break;
        case 'e':
        case Key::ESC:
            nextScreen = new Game(Color::TAN);
            delete background;
            background = NULL;
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
    Screen* nextScreen = NULL;
    
    if (click.x >= resumeText.getLocationX() && 
            click.x < resumeText.getLocationX()+resumeText.getWidth() &&
        click.y >= resumeText.getLocationY() && 
            click.y < resumeText.getLocationY()+resumeText.getHeight())
    {
        nextScreen = background;
        background = NULL;
    } else if (
        click.x >= exitText.getLocationX() && 
            click.x < exitText.getLocationX()+exitText.getWidth() &&
        click.y >= exitText.getLocationY() && 
            click.y < exitText.getLocationY()+exitText.getHeight())
    {
        nextScreen = new Game(Color::TAN);
        delete background;
        background = NULL;
    }
    
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
    
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= resumeText.getLocationX() && 
            cursorX < resumeText.getLocationX()+resumeText.getWidth() &&
        cursorY >= resumeText.getLocationY() && 
            cursorY < resumeText.getLocationY()+resumeText.getHeight())
    {
        resumeText.setForeground(Color::REAL_GREEN);
    } else if (
        cursorX >= exitText.getLocationX() && 
            cursorX < exitText.getLocationX()+exitText.getWidth() &&
        cursorY >= exitText.getLocationY() && 
            cursorY < exitText.getLocationY()+exitText.getHeight())
    {
        exitText.setForeground(Color::DARK_RED);
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
    
    if (background) {
        background->applyLayout();
        background->draw();
    }
    
    char* sharedPixelBuffer = g->getBuffer();
    
    // Darkens the screen
    for (int i = 0; i < g->getBufferLen(); i++) {
        sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/3;
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
        
        if (background) {
            background->erase();
        }
        
        isVisible = false;
    }
}


/* ---------- Private ---------- */

/*
 * Initializes this PauseScreen
 */
void PauseScreen::init() {
    /* Eww */
    // Craft the "resume" text shape
    resumeText
    /*R*/.addBlock<Block>(0, 0).addBlock<Block>(0, 1).addBlock<Block>(0, 2).addBlock<Block>(0, 3)
            .addBlock<Block>(0, 4).addBlock<Block>(1, 1).addBlock<Block>(1, 2)
            .addBlock<Block>(1, 4).addBlock<Block>(2, 0).addBlock<Block>(2, 2)
            .addBlock<Block>(2, 3).addBlock<Block>(2, 4)
    /*E*/.addBlock<Block>(4, 0).addBlock<Block>(4, 1).addBlock<Block>(4, 2).addBlock<Block>(4, 3)
            .addBlock<Block>(4, 4).addBlock<Block>(5, 0).addBlock<Block>(5, 2)
            .addBlock<Block>(5, 4).addBlock<Block>(6, 0).addBlock<Block>(6, 4)
    /*S*/.addBlock<Block>(8, 0).addBlock<Block>(8, 2).addBlock<Block>(8, 3).addBlock<Block>(8, 4)
            .addBlock<Block>(9, 0).addBlock<Block>(9, 2).addBlock<Block>(9, 4)
            .addBlock<Block>(10, 0).addBlock<Block>(10, 1).addBlock<Block>(10, 2)
            .addBlock<Block>(10, 4)
    /*U*/.addBlock<Block>(12, 0).addBlock<Block>(12, 1).addBlock<Block>(12, 2)
            .addBlock<Block>(12, 3).addBlock<Block>(12, 4).addBlock<Block>(13, 0)
            .addBlock<Block>(14, 0).addBlock<Block>(14, 1).addBlock<Block>(14, 2)
            .addBlock<Block>(14, 3).addBlock<Block>(14, 4)
    /*M*/.addBlock<Block>(16, 0).addBlock<Block>(16, 1).addBlock<Block>(16, 2)
            .addBlock<Block>(16, 3).addBlock<Block>(16, 4).addBlock<Block>(17, 2)
            .addBlock<Block>(17, 3).addBlock<Block>(18, 0).addBlock<Block>(18, 1)
            .addBlock<Block>(18, 2).addBlock<Block>(18, 3).addBlock<Block>(18, 4)
    /*E*/.addBlock<Block>(20, 0).addBlock<Block>(20, 1).addBlock<Block>(20, 2)
            .addBlock<Block>(20, 3).addBlock<Block>(20, 4).addBlock<Block>(21, 0)
            .addBlock<Block>(21, 2).addBlock<Block>(21, 4).addBlock<Block>(22, 0)
            .addBlock<Block>(22, 4);

    exitText
    /*E*/.addBlock<Block>(0, 0).addBlock<Block>(0, 1).addBlock<Block>(0, 2).addBlock<Block>(0, 3)
            .addBlock<Block>(0, 4).addBlock<Block>(1, 0).addBlock<Block>(1, 2)
            .addBlock<Block>(1, 4).addBlock<Block>(2, 0).addBlock<Block>(2, 4)
    /*X*/.addBlock<Block>(4, 0).addBlock<Block>(4, 1).addBlock<Block>(4, 3).addBlock<Block>(4, 4)
            .addBlock<Block>(5, 2).addBlock<Block>(6, 0).addBlock<Block>(6, 1)
            .addBlock<Block>(6, 3).addBlock<Block>(6, 4)
    /*I*/.addBlock<Block>(8, 0).addBlock<Block>(8, 4).addBlock<Block>(9, 0).addBlock<Block>(9, 1)
            .addBlock<Block>(9, 2).addBlock<Block>(9, 3).addBlock<Block>(9, 4)
            .addBlock<Block>(10, 0).addBlock<Block>(10, 4)
    /*T*/.addBlock<Block>(12, 4).addBlock<Block>(13, 0).addBlock<Block>(13, 1)
            .addBlock<Block>(13, 2).addBlock<Block>(13, 3).addBlock<Block>(13, 4)
            .addBlock<Block>(14, 4);
    
    resumeText.setForeground(Color::GREEN);
    exitText.setForeground(Color::RED);
}
