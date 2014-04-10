/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 10, 2014
 */

#include "Game.h"

Game::Game(): Screen() {
    init();
}

Game::~Game() {
    erase();
    delete field;
    delete currentTetromino;
    delete shadow;
}


/* ---------- Private ---------- */

void Game::init() {
    srand(time(0));
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
    
    // Spawn a new tetromino and create a shadow in the same place
    field = new PlayingField(10+getLocationX(), 10+getLocationY(), 10, 20, 15, 2, Color::WHITE, Color::BLACK);
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


/* ---------- Implemented from Screen ---------- */


void Game::respondToKey(int key) {
    switch (key) {
        case 'w':
        case 165: // UP
            // If we can shift the current tetromino up within the block field, do so
            if (field->canShiftUp(currentTetromino)) {
                currentTetromino->erase();
                currentTetromino->shiftUp();
                currentTetromino->draw();
            }
            
            break;
        case 'a':
        case 164: // LEFT
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
        case 167: // DOWN
            // If we can shift the current tetromino down within the block field, do so
            if (field->canShiftDown(currentTetromino)) {
                currentTetromino->erase();
                currentTetromino->shiftDown();
                currentTetromino->draw();
            }
            
            break;
        case 'd':
        case 166: // RIGHT
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
        case 'q':
            // If we can rotate the current tetromino CCW within the block field, do so
            if (field->canRotateCCW(currentTetromino)) {
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
            
            break;
        case 'e': // Rotate CW
            // If we can rotate the current tetromino CW within the block field, do so
            if (field->canRotateCW(currentTetromino)) {
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
            
            field->mergeAndDelete(currentTetromino); // Merge the current tetromino into the playing field
            
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
        default:
            cout << key << endl;
    }
}

void Game::respondToClick(Click click) {
    // Do nothing
}


/* ---------- Implemented from Drawable ---------- */

void Game::draw() {
    field->draw();
    shadow->draw();
    currentTetromino->draw();
    
    isVisible = true;
}

void Game::erase() {
    if (isVisible) {
        currentTetromino->erase();
        shadow->erase();
        field->erase();
        
        isVisible = false;
    }
}
