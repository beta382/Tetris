/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 15, 2014
 */

#include "Game.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Game object using the passed foreground color or default values.
 * 
 * Parameters:
 *   unsigned int color: The value to initialize this Game object's foreground with, defaults to
 *     Color::BLACK
 */
Game::Game(unsigned int color): 
Screen(color),
        field(10+x, 10+y, 10, 20, 16, 2, Color::WHITE, foreground),
        bgRectNext(field.getLocationX()+field.getWidth() + 20, 250, 
                field.getTotalBlockSize()*5+field.getPadding(), 
                field.getTotalBlockSize()*3+field.getPadding(), Color::LIGHT_TAN, foreground),
        bgRectNext2(bgRectNext.getLocationX()-2, bgRectNext.getLocationY()-2,
                bgRectNext.getWidth()+4, bgRectNext.getHeight()+4, Color::DARK_TAN, foreground)
{
    init();
}

/*
 * Destructs this Game object.
 */
Game::~Game() {
    erase();
    delete currentTetromino;
    delete shadow;
}


/* ---------- Implemented from Screen ---------- */

/*
 * Performs an action based on the passed key.
 * 
 * Parameters:
 *   int key: The value of the key to perform an action based upon
 *   
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
Screen* Game::respondToKey(int key) {
    switch (key) {
        case 'w':
        case Key::UP: // UP
            doShiftUp();
            break;
        case 'a':
        case Key::LEFT: // LEFT
            doShiftLeft();
            break;
        case 's':
        case Key::DOWN: // DOWN
            doShiftDown();
            break;
        case 'd':
        case Key::RIGHT: // RIGHT
            doShiftRight();
            break;
        case 'q': // Rotate CCW
            // If we can rotate the current tetromino CCW within the block field, do so
            if (field.canRotateCCW(currentTetromino)) {
                doRotateCCW();
            } else { // If we can't, try doing a wall kick
                currentTetromino->erase();
                currentTetromino->shiftLeft();
                if (field.canRotateCCW(currentTetromino)) {
                    doRotateCCW();
                } else { // Reset, try other direction
                    currentTetromino->shiftRight();
                    currentTetromino->shiftRight();
                    
                    if (field.canRotateCCW(currentTetromino)) {
                        doRotateCCW();
                    } else { // Reset
                        currentTetromino->shiftLeft();
                        currentTetromino->draw();
                    }
                }
            }
            
            break;
        case 'e': // Rotate CW
            // If we can rotate the current tetromino CW within the block field, do so
            if (field.canRotateCW(currentTetromino)) {
                doRotateCW();
            } else { // If we can't, try doing a wall kick
                currentTetromino->erase();
                currentTetromino->shiftRight();
                if (field.canRotateCW(currentTetromino)) {
                    doRotateCW();
                } else { // Reset, try other direction
                    currentTetromino->shiftLeft();
                    currentTetromino->shiftLeft();
                    
                    if (field.canRotateCW(currentTetromino)) {
                        doRotateCW();
                    } else { // Reset
                        currentTetromino->shiftRight();
                        currentTetromino->draw();
                    }
                }
            }
            
            break;
        case 'n': // New tetromino. This is solely for testing, it spawns a new tetromino without merging.
            doResetTetromino<Block>();
            break;
        case 'j': // Join tetromino. Forcefully merges the current tetromino into the playing field.
            doJoinAndRespawn();
            break;
        case 'g': // Spawn special tetromino for testing
            doResetTetromino<ExplodingBlock>();
            break;
        default:
            cout << key << endl;
    }
    
    return NULL;
}

/*
 * Performs an action based on the passed Click.
 * 
 * Parameters:
 *   Click: The value of the Click to perform an action based upon
 *            
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
Screen* Game::respondToClick(Click click) {
    // Do nothing for now
    return NULL;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 */
void Game::doBackground() {
    // Just redraw for now
    draw();
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void Game::draw() {
    bgRect.draw();
    field.draw();
    shadow->draw();
    currentTetromino->draw();
    
    bgRectNext2.draw();
    bgRectNext.draw();
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void Game::erase() {
    if (isVisible) {
        currentTetromino->erase();
        shadow->erase();
        field.erase();
        bgRect.erase();
        
        isVisible = false;
    }
}


/* ---------- Private ---------- */

/*
 * Instantiates this Game object's dynamically allocated member data and starts the RNG.
 */
void Game::init() {
    srand(time(0));
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
    
    // Spawn a new tetromino and create a shadow in the same place
    currentTetromino = field.spawnNewTetromino<Block>(shape);
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), 
            currentTetromino->getLocationY(), currentTetromino->getBlockSize(),
            currentTetromino->getPadding(), shape, field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    draw();
}

/*
 * Properly performs a shift up on currentTetromino WITHOUT performing checks.
 */
void Game::doShiftUp() {
    if (field.canShiftUp(currentTetromino)) {
        currentTetromino->erase();
        currentTetromino->shiftUp();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift down on currentTetromino WITHOUT performing checks.
 */
void Game::doShiftDown() {
    if (field.canShiftDown(currentTetromino)) {
        currentTetromino->erase();
        currentTetromino->shiftDown();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift left on currentTetromino WITHOUT performing checks.
 */
void Game::doShiftLeft() {
    if (field.canShiftLeft(currentTetromino)) {
        // Erase and move the current tetromino, but don't redraw it just yet
        currentTetromino->erase();
        currentTetromino->shiftLeft();
        
        // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
        shadow->erase();
        shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
        shadow->draw();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift right on currentTetromino WITHOUT performing checks.
 */
void Game::doShiftRight() {
    if (field.canShiftRight(currentTetromino)) {
        // Erase and move the current tetromino, but don't redraw it just yet
        currentTetromino->erase();
        currentTetromino->shiftRight();
        
        // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
        shadow->erase();
        shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
        shadow->draw();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a clockwise rotation on currentTetromino WITHOUT performing checks.
 */
void Game::doRotateCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCW();
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the
    // rotation, and then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCW();
    
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the
    // shadow
    shadow->draw();
    currentTetromino->draw();
}

/*
 * Properly performs a counter-clockwise rotation on currentTetromino WITHOUT performing checks.
 */
void Game::doRotateCCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCCW();       
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the
    // rotation, and then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCCW();
    
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the
    // shadow
    shadow->draw();
    currentTetromino->draw();
}

/*
 * Joins the currentTetromino with the field and spawns a new one.
 */
void Game::doJoinAndRespawn() {
    delete shadow;
    field.mergeAndDelete(currentTetromino);
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7);
    
    int blockType = rand()%(1 << 16); // 16-bit number
        
    // Spawn a new tetromino and create a shadow in the same place
    
    if (blockType < (1 << 16)/20) {
        currentTetromino = field.spawnNewTetromino<ExplodingBlock>(shape);
    } else if (blockType < (2*(1 << 16))/20) {
        currentTetromino = field.spawnNewTetromino<GravityBlock>(shape);
    } else {
        currentTetromino = field.spawnNewTetromino<Block>(shape);
    }
    
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
            currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape,
            field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
    shadow->draw();
    currentTetromino->draw();
}
