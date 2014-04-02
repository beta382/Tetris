/*
 * Tetris.cpp
 *
 *  Created on: Mar 31, 2014
 *  Modified on: Mar 31, 2014
 *  Author: D. Booth
 */

#include "Tetris.h"

//Tetris Constructor

Tetris::Tetris(GLUT_Plotter* g): Drawable(g) {
    init();
}

Tetris::Tetris(GLUT_Plotter *g, int x, int y): Drawable(g, x, y) {
    init();
}

Tetris::~Tetris() {
    erase();
    delete field;
    delete currentTetromino;
}

//Tetris Main Game Loop
void Tetris::Play (void) {
    
    //Check for Keyboard Hit
    while(g->kbhit()){
        int k = g->getKey();
        
        switch (k) {
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
                field->draw();
                
                currentTetromino = field->spawnNewTetromino(static_cast<TetrominoShape>(rand() % 7));
                currentTetromino->draw();
                break;
            case 27: // ESC
            case 'x':
                exit(1);
                break;
        }
    }
    
    
    //Check for mouse click
    while (g->click()) {
        
        Click c;
        c = g->getClick();
    }
    
    // Update screen - draw game
    g->Draw();
}


/* ---------- Private ---------- */

void Tetris::init() {
    field = new PlayingField(g, 10+getLocationX(), 10+getLocationY());
    currentTetromino = field->spawnNewTetromino(S);
    currentTetromino->draw();
    
    srand(time(0));
}

/* ---------- Implemented from Drawable ---------- */

void Tetris::draw() {
    field->draw();
    currentTetromino->draw();
}

void Tetris::erase() {
    field->erase();
    currentTetromino->erase();
}
