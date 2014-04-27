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

Tetris::Tetris(GLUT_Plotter* g):
        g(g), screen(new Game(Color::TAN))
{
}

Tetris::~Tetris() {
    delete screen;
}

//Tetris Main Game Loop
void Tetris::Play (void) {
    
    Screen* newScreen = NULL;
    
    //Check for Keyboard Hit
    while (g->kbhit()) {
        int k = g->getKey();
        
        switch (k) {
            case Key::ESC: // ESC
            case 'x':
                delete this;
                
                leakcheck::report(cout);
                exit(0);
                break;
            case 'p':
                leakcheck::report(cout);
                break;
            default:
                newScreen = screen->respondToKey(k);
                break;
        }
    }

    checkNewScreen();
    
    //Check for mouse click
    while (g->click()) {
        Click c = g->getClick();
        
        newScreen = screen->respondToClick(c);
    }
    
    checkNewScreen();
    
    //Do the screen's background function
    newScreen = screen->doBackground();
    checkNewScreen();
    
    // Update screen - draw game
    g->Draw();
}
