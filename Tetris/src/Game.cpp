/*
 * Game.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: Austin
 */

#include "Game.h"

Game::Game(GLUT_Plotter *g): Drawable(g) {
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
            currentTetromino->setColor(rand() % 16);
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
        case 27: // ESC
        case 'x':
            exit(1);
            break;
        default:
            cout << key << endl;
    }
}


/* ---------- Private ---------- */

void Game::init() {
    srand(time(0));
    
    field = new PlayingField(g, 10+getLocationX(), 10+getLocationY());
    currentTetromino = field->spawnNewTetromino<Block>(static_cast<TetrominoShape>(rand() %7));
    currentTetromino->draw();
}


/* ---------- Implemented from Drawable ---------- */

void Game::draw() {
    field->draw();
    currentTetromino->draw();
    
    isVisible = true;
}

void Game::erase() {
    if (isVisible) {
        field->erase();
        currentTetromino->erase();
        
        isVisible = false;
    }
}
