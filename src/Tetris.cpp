/*
 * Author:                 Dr. Booth, Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 31, 2014
 * Date last modified:     Apr 11, 2014
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
    
    Screen *newScreen = NULL;
    
    //Check for Keyboard Hit
    while (g->kbhit()) {
        int k = g->getKey();
        
        switch (k) {
            case 27: // ESC
            case 'x':
                exit(1);
                break;
            default:
                newScreen = screen->respondToKey(k);
        }
    }
    
    // If we don't get NULL back from respondToClicik, it means we went to a new screen, so delete the old screen and 
    // set it to the new screen, and then exit this function
    if (newScreen) {
        delete screen;
        screen = newScreen;
        return;
    }
    
    //Check for mouse click
    while (g->click()) {
        Click c = g->getClick();
        
        newScreen = screen->respondToClick(c);
    }
    
    // If we don't get NULL back from respondToClicik, it means we went to a new screen, so delete the old screen and 
    // set it to the new screen, and then exit this function
    if (newScreen) {
        delete screen;
        screen = newScreen;
        return;
    }
    
    //Do the screen's background function
    screen->doBackground();
    
    // Update screen - draw game
    g->Draw();
}
