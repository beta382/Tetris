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

void Tetris::init() {
    field = new PlayingField(g, 10+getLocationX(), 10+getLocationY());
    currentTetromino = field->spawnNewTetromino(3, 0, S);
    currentTetromino->draw();
    
    srand(time(0));
}


//Tetris Main Game Loop
void Tetris::Play (void) {
    
    //Check for Keyboard Hit
    while(g->kbhit()){
        int k = g->getKey();
        
        int prevX, prevY;
        
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
                prevX = currentTetromino->getLocationX();
                prevY = currentTetromino->getLocationY();
                
                delete currentTetromino;
                currentTetromino = field->spawnNewTetromino(prevX-field->getLocationX(), prevY-field->getLocationY(), 
                        static_cast<TetrominoShape>(rand() % 7));
                currentTetromino->draw();
                break;
            case 'j':
                field->merge(currentTetromino);
                field->draw();
                
                currentTetromino = field->spawnNewTetromino(3, 3, static_cast<TetrominoShape>(rand() % 7));
                currentTetromino->draw();
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

/* ---------- Implemented from Drawable ---------- */
void Tetris::draw() {
    field->draw();
    currentTetromino->draw();
}

void Tetris::erase() {
    field->erase();
    currentTetromino->erase();
}
