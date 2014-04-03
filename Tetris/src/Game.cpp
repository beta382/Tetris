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
            if (field->canShiftUp(currentTetromino)) {
                currentTetromino->shiftUp();
            }
            break;
        case 'a':
            if (field->canShiftLeft(currentTetromino)) {
                currentTetromino->shiftLeft();
            }
            break;
        case 's':
            if (field->canShiftDown(currentTetromino)) {
                currentTetromino->shiftDown();
            }
            break;
        case 'd':
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
            currentTetromino = field->spawnNewTetromino(static_cast<TetrominoShape>(rand() % 7));
            currentTetromino->draw();
            break;
        case 'j':
            field->merge(currentTetromino);
            
            currentTetromino = field->spawnNewTetromino(static_cast<TetrominoShape>(rand() % 7));
            currentTetromino->draw();
            break;
        case 27: // ESC
        case 'x':
            exit(1);
            break;
    }
}


/* ---------- Private ---------- */

void Game::init() {
    field = new PlayingField(g, 10+getLocationX(), 10+getLocationY());
    currentTetromino = field->spawnNewTetromino(S);
    currentTetromino->draw();
    
    srand(time(0));
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
