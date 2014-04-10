/*
 * Tetris.cpp
 *
 *  Created on: Mar 31, 2014
 *  Modified on: Mar 31, 2014
 *  Author: D. Booth
 */

#include "Tetris.h"

//Tetris Constructor

Tetris::Tetris(GLUT_Plotter *g) {
    this->g = g;
    screen = new Game(); // This is temporary, change it to whatever you need to test
}

Tetris::~Tetris() {
    delete screen;
}

//Tetris Main Game Loop
void Tetris::Play (void) {
    
    //Check for Keyboard Hit
    while (g->kbhit()) {
        int k = g->getKey();
        
        switch (k) {
            case 27: // ESC
            case 'x':
                exit(1);
                break;
            default:
                screen->respondToKey(k);
        }
    }
    
    //Check for mouse click
    while (g->click()) {
        Click c = g->getClick();
        
        screen->respondToClick(c);
    }
    
    // Update screen - draw game
    g->Draw();
}
