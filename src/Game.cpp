/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr  8, 2014
 */

#include "Game.h"

Game::Game(): Drawable() {
    init();
}

Game::~Game() {
    erase();
    delete field;
    delete currentTetromino;
}

void Game::respondToKey(int key) {
    switch (key) {
        case 'w':
        case 165: // UP
            if (field->canShiftUp(currentTetromino)) {
                currentTetromino->shiftUp();
            }
            break;
        case 'a':
        case 164: // LEFT
            if (field->canShiftLeft(currentTetromino)) {
                currentTetromino->shiftLeft();
            }
            break;
        case 's':
        case 167: // DOWN
            if (field->canShiftDown(currentTetromino)) {
                currentTetromino->shiftDown();
            }
            break;
        case 'd':
        case 166: // RIGHT
            if (field->canShiftRight(currentTetromino)) {
                currentTetromino->shiftRight();
            }
            break;
        case 'c':
            currentTetromino->setForeground(rand() % 16);
            currentTetromino->draw();
            break;
        case 'q':
            if (field->canRotateCCW(currentTetromino)) {
                currentTetromino->rotateCCW();
            }
            break;
        case 'e':
            if (field->canRotateCW(currentTetromino)) {
                currentTetromino->rotateCW();
            }
            break;
        case 'n':
            delete currentTetromino;
            currentTetromino = field->spawnNewTetromino<Block>(static_cast<TetrominoShape>(rand() % 7));
            currentTetromino->draw();
            break;
        case 'j':
            field->mergeAndDelete(currentTetromino);
            
            currentTetromino = field->spawnNewTetromino<Block>(static_cast<TetrominoShape>(rand() % 7));
            currentTetromino->draw();
            break;
        case 'g':
            delete currentTetromino;
            currentTetromino = field->spawnNewTetromino<GhostBlock>(static_cast<TetrominoShape>(rand() %7));
            currentTetromino->draw();
            break;
        default:
            cout << key << endl;
    }
}


/* ---------- Private ---------- */

void Game::init() {
    srand(time(0));
    
    field = new PlayingField(10+getLocationX(), 10+getLocationY(), 10, 20, Color::WHITE, Color::RED);
    currentTetromino = field->spawnNewTetromino<Block>(static_cast<TetrominoShape>(rand() %7));

    draw();
}


/* ---------- Implemented from Drawable ---------- */

void Game::draw() {
    field->draw();
    currentTetromino->draw();
    
    isVisible = true;
}

void Game::erase() {
    if (isVisible) {
        currentTetromino->erase();
        field->erase();
        
        isVisible = false;
    }
}
