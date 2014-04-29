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
 *   Screen* return: A pointer to the screen object to return to
 */
PauseScreen::PauseScreen(Screen* background):
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
    
    if (click.x > resumeText.getLocationX() && 
            click.x < resumeText.getLocationX()+resumeText.getWidth() &&
        click.y > resumeText.getLocationY() && 
        click.y < resumeText.getLocationY()+resumeText.getHeight())
    {
        nextScreen = background;
        background = NULL;
    } else if (
        click.x > exitText.getLocationX() && 
            click.x < exitText.getLocationX()+exitText.getWidth() &&
        click.y > exitText.getLocationY() && 
            click.y < exitText.getLocationY()+exitText.getHeight())
    {
        nextScreen = new Game(Color::TAN);
        delete background;
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
    
    if (cursorX > resumeText.getLocationX() && 
            cursorX < resumeText.getLocationX()+resumeText.getWidth() &&
        cursorY > resumeText.getLocationY() && 
            cursorY < resumeText.getLocationY()+resumeText.getHeight())
    {
        resumeText.setForeground(Color::REAL_GREEN);
    } else if (
        cursorX > exitText.getLocationX() && 
            cursorX < exitText.getLocationX()+exitText.getWidth() &&
        cursorY > exitText.getLocationY() && 
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
    resumeText.addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*0, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*0, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize(), 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*0, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*0, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*0, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize(), 
                resumeText.getLocationY()+resumeText.getTotalBlockSize(), 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize(), 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize(), 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*2, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*2, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*2, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*2, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
                
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*4, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*4, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*4, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*4, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*4, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*5, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*5, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*5, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*6, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*6, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*8, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*8, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*8, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*8, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*9, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*9, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*9, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*10, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*10, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*10, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*10, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*12, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*12, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*12, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*12, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*12, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*13, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*14, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*14, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*14, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*14, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*14, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
                
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*16, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*16, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*16, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*16, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*16, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*17, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*17, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*18, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*18, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*18, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*18, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*18, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*20, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*20, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*1, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*20, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*20, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*3, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*20, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*21, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*21, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*2, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*21, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*22, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*0, 
                resumeText.getBlockSize(), resumeText.getPadding())).addBlock(
        new Block(resumeText.getLocationX()+resumeText.getTotalBlockSize()*22, 
                resumeText.getLocationY()+resumeText.getTotalBlockSize()*4, 
                resumeText.getBlockSize(), resumeText.getPadding())
    ); /* End resumeText */
    
    // Craft the "exit" text shape
    exitText.addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*0, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*0, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*1, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*0, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*2, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*0, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*3, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*0, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*1, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*1, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*2, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*1, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*2, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*2, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*4, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*4, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*1, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*4, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*3, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*4, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*5, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*2, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*6, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*6, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*1, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*6, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*3, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(        
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*6, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
                        
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*8, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*8, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*9, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*9, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*1, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*9, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*2, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*9, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*3, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*9, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(        
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*10, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*10, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*12, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*13, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*0, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*13, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*1, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*13, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*2, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*13, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*3, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*13, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())).addBlock(
        new Block(exitText.getLocationX()+exitText.getTotalBlockSize()*14, 
                exitText.getLocationY()+exitText.getTotalBlockSize()*4, 
                exitText.getBlockSize(), exitText.getPadding())
    ); /* End exitText */
    
    resumeText.setForeground(Color::GREEN);
    exitText.setForeground(Color::RED);
    
    
}
