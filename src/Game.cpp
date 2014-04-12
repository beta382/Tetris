/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 11, 2014
 */

#include "Game.h"

/*
 * Instantiates a Game object using the passed foreground color
 * 
 * color defaults to Color::BLACK if nothing is passed
 * 
 * Calls Screen(color)
 * Calls init()
 */
Game::Game(unsigned int color): 
Screen(color)
{
    init();
}

/*
 * Properly destructs a Game object
 * 
 * Calls erase()
 * Deletes field, currentTetromino, and shadow
 */
Game::~Game() {
    erase();
    delete field;
    delete currentTetromino;
    delete shadow;
}


/* ---------- Private ---------- */

/*
 * Instantiates dynamically allocated member data, performs initial game screen setup
 * 
 * Dynamically allocates a PlayingField, a Tetromino<Block>, and a Tetromino<GhostBlock>
 * Moves the Tetromino<GhostBlock> to it's proper location on the screen
 * Calls draw()
 */
void Game::init() {
    srand(time(0));
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
    
    // Spawn a new tetromino and create a shadow in the same place
    field = new PlayingField(10+getLocationX(), 10+getLocationY(), 10, 20, 15, 2, Color::WHITE, getForeground());
    currentTetromino = field->spawnNewTetromino<Block>(shape);
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), 
            currentTetromino->getLocationY(), currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape, 
            field->getForeground());
    
    // Have the shadow fall
    while (field->canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    draw();
}

/*
 * Does a clockwise rotation on currentTetromino WITHOUT performing checks, while properly updating
 *   shadow's position on the screen
 */
void Game::doRotateCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCW();
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the rotation, and
    // then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCW();
    
    while (field->canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
    shadow->draw();
    currentTetromino->draw();
}

/*
 * Does a counter-clockwise rotation on currentTetromino WITHOUT performing checks, while properly
 *   updating shadow's position on the screen
 */
void Game::doRotateCCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCCW();       
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the rotation, and
    // then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCCW();
    
    while (field->canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
    shadow->draw();
    currentTetromino->draw();
}


/* ---------- Implemented from Screen ---------- */

/*
 * Performs an action based on the passed key. Some of these currently exist only for testing
 *   purposes.
 * 
 * If key is 'w' or UP, shift the currentTetromino up
 * If key is 'a' or LEFT, shift the currentTetromino left
 * If key is 's' or DOWN, shift the currentTetromino down
 * If key is 'd' or RIGHT, shift the currentTetromino right
 * If key is 'q', rotate the currentTetromino counter-clockwise
 * If key is 'e', rotate the currentTetromino clockwise
 * If key is 'n', spawn a new Tetromino<BlockType> without joining the current one with the field
 * If key is 'j', join the currentTetromino with the field and 
 * If key is 'g', spawn a new Tetromino<GhostBlock> without joining the current one with the field
 * Else, print the value of the key to the console
 * 
 * Returns a pointer to a Screen object that control should shift to after this function exits, or
 *   NULL if control should remain unchanged.
 */
Screen *Game::respondToKey(int key) {
    switch (key) {
        case 'w':
        case Key::UP: // UP
            // If we can shift the current tetromino up within the block field, do so
            if (field->canShiftUp(currentTetromino)) {
                currentTetromino->erase();
                currentTetromino->shiftUp();
                currentTetromino->draw();
            }
            
            break;
        case 'a':
        case Key::LEFT: // LEFT
            // If we can shift the current tetromino left within the block field, do so
            if (field->canShiftLeft(currentTetromino)) {
                // Erase and move the current tetromino, but don't redraw it just yet
                currentTetromino->erase();
                currentTetromino->shiftLeft();
                
                // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
                shadow->erase();
                shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
                while (field->canShiftDown(shadow)) {
                    shadow->shiftDown();
                }
                
                // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
                shadow->draw();
                currentTetromino->draw();
            }
            
            break;
        case 's':
        case Key::DOWN: // DOWN
            // If we can shift the current tetromino down within the block field, do so
            if (field->canShiftDown(currentTetromino)) {
                currentTetromino->erase();
                currentTetromino->shiftDown();
                currentTetromino->draw();
            }
            
            break;
        case 'd':
        case Key::RIGHT: // RIGHT
            // If we can shift the current tetromino right within the block field, do so
            if (field->canShiftRight(currentTetromino)) {
                // Erase and move the current tetromino, but don't redraw it just yet
                currentTetromino->erase();
                currentTetromino->shiftRight();
                
                // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
                shadow->erase();
                shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
                while (field->canShiftDown(shadow)) {
                    shadow->shiftDown();
                }
                
                // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
                shadow->draw();
                currentTetromino->draw();
            }
            
            break;
        case 'q': // Rotate CCW
            // If we can rotate the current tetromino CCW within the block field, do so
            if (field->canRotateCCW(currentTetromino)) {
                doRotateCCW();
            } else { // If we can't, try doing a wall kick
                bool didRotate = false;
                
                // Try shifting to the left and then rotating
                if (field->canShiftLeft(currentTetromino)) {
                    currentTetromino->erase();
                    currentTetromino->shiftLeft();
                    
                    if (field->canRotateCCW(currentTetromino)) {
                        doRotateCCW();
                        didRotate = true; // If we succeeded, make a note
                    } else { // If we didn't succeed, reset
                        currentTetromino->shiftRight();
                        currentTetromino->draw();
                    }
                    
                } 
                
                // If the previous attempt wasn't successful, try shifting to the right and then rotating
                if (field->canShiftRight(currentTetromino) && !didRotate) {
                    currentTetromino->erase();
                    currentTetromino->shiftRight();
                    
                    if (field->canRotateCCW(currentTetromino)) {
                        doRotateCCW();
                    } else { // If we didn't succeed, reset
                        currentTetromino->shiftLeft();
                        currentTetromino->draw();
                    }
                }
            }
            
            break;
        case 'e': // Rotate CW
            // If we can rotate the current tetromino CW within the block field, do so
            if (field->canRotateCW(currentTetromino)) {
                doRotateCW();
            } else { // If we can't, try doing a wall kick
                bool didRotate = false;
                
                // Try shifting to the left and then rotating
                if (field->canShiftLeft(currentTetromino)) {
                    currentTetromino->erase();
                    currentTetromino->shiftLeft();
                    
                    if (field->canRotateCW(currentTetromino)) {
                        doRotateCW();
                        didRotate = true; // If we succeeded, make a note
                    } else { // If we didn't succeed, reset
                        currentTetromino->shiftRight();
                        currentTetromino->draw();
                    }
                    
                } 
                
                // If the previous attempt wasn't successful, try shifting to the right and then rotating
                if (field->canShiftRight(currentTetromino) && !didRotate) {
                    currentTetromino->erase();
                    currentTetromino->shiftRight();
                    
                    if (field->canRotateCW(currentTetromino)) {
                        doRotateCW();
                    } else { // If we didn't succeed, reset
                        currentTetromino->shiftLeft();
                        currentTetromino->draw();
                    }
                }
            }
            
            break;
        case 'n': // New tetromino. This is solely for testing, it spawns a new tetromino without merging.
            // Delete the current tetromino and its shadow
            delete currentTetromino;
            delete shadow;
            
            { // C++ throws a fit about variables in case statements, so this just sets a scope for `shape`
                TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
                
                // Spawn a new tetromino and create a shadow in the same place
                currentTetromino = field->spawnNewTetromino<Block>(shape);
                shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
                        currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape,
                        field->getForeground());
            }
            
            // Have the shadow fall
            while (field->canShiftDown(shadow)) {
                shadow->shiftDown();
            }
            
            // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
            shadow->draw();
            currentTetromino->draw();
            
            break;
        case 'j': // Join tetromino. Forcefully merges the current tetromino into the playing field.
            delete shadow; // Delete the current tetromino's shadow
            cout << endl << endl;
            field->mergeAndDelete(currentTetromino); // Merge the current tetromino into the playing field
            
            { // C++ throws a fit about variables in case statements, so this just sets a scope for shape
                TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
                
                // Spawn a new tetromino and create a shadow in the same place
                currentTetromino = field->spawnNewTetromino<Block>(shape);
                shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
                        currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape,
                        field->getForeground());
            }
            
            // Have the shadow fall
            while (field->canShiftDown(shadow)) {
                shadow->shiftDown();
            }
            
            // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
            shadow->draw();
            currentTetromino->draw();
            
            break;
        case 'g': // Spawn Ghost tetromino for testing
            delete currentTetromino;
            delete shadow;
            
            { // C++ throws a fit about variables in case statements, so this just sets a scope for shape
                TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
                
                // Spawn a new tetromino and create a shadow in the same place
                currentTetromino = field->spawnNewTetromino<GhostBlock>(shape);
                shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
                        currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape,
                        field->getForeground());
            }
            
            // Have the shadow fall
            while (field->canShiftDown(shadow)) {
                shadow->shiftDown();
            }
            
            // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
            shadow->draw();
            currentTetromino->draw();
            break;
        default:
            cout << key << endl;
    }
    
    return NULL;
}

/*
 * Performs an action based on the passed Click
 * 
 * Currently does nothing
 * 
 * Returns a pointer to a Screen object that control should shift to after this function exits, or
 *   NULL if control should remain unchanged.
 */
Screen *Game::respondToClick(Click click) {
    // Do nothing for now
    return NULL;
}

/*
 * Performs actions that should happen continuously in the background on the Game screen
 * 
 * Calls draw()
 */
void Game::doBackground() {
    // Just redraw for now
    draw();
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy
 * 
 * Sets isVisible to true
 */
void Game::draw() {
    bgRect.draw();
    field->draw();
    shadow->draw();
    currentTetromino->draw();
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy and sets
 *   isVisible to false, only if isVisible is true
 */
void Game::erase() {
    if (isVisible) {
        currentTetromino->erase();
        shadow->erase();
        field->erase();
        bgRect.erase();
        
        isVisible = false;
    }
}









