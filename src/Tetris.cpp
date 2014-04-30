/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 31, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "Tetris.h"

//Tetris Constructor

Tetris::Tetris(GLUT_Plotter* g):
        g(g), screen(new MenuScreen(Color::TAN))
{
}

Tetris::~Tetris() {
    delete screen;
}

//Tetris Main Game Loop
void Tetris::Play (void) {
    try {
        //Check for Keyboard Hit
        while (g->kbhit()) {
            int k = g->getKey();
            
            switch (k) {
                case '`':
                    leakcheck::report(cout);
                    break;
                default:
                    screen->respondToKey(k);
                    break;
            }
        }
        
        //Check for mouse click
        while (g->click()) {
            Click c = g->getClick();
            
            screen->respondToClick(c);
        }
        
        //Do the screen's background function
        screen->doBackground();
        
        // Update screen - draw game
        g->Draw();
    } catch (QUIT& e) {
        delete this;
        
        leakcheck::report(cout);
        exit(0);
    } catch (NEW_SCREEN& e) {
        
        if (!screen->shouldRetain()) {
            delete screen;
        }
        
        screen = e.screen;
    }
}
