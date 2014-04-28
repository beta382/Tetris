/*
 * Tetris.h - Tetris game class header
 *
 *  Created on: Mar 28, 2014
 *  Created on: Mar 28, 2014
 *      Author: Dr. Booth
 */

#ifndef TETRIS_H_
#define TETRIS_H_

/*
 * A handy macro for code consolidation within Play, since the code in question can't go in a
 *   function. Checks if we have a new screen to go to, and goes to it if we do.
 */
#define _checkNewScreen() \
    if (newScreen) { \
        if (!screen->shouldRetain()) { \
            delete screen; \
        } \
        screen = newScreen; \
        return; \
    }

#include "GLUT_Plotter.h"
#include "screens.h"
#include "util.h"

class Tetris {
    public:
        //constructor
        Tetris(GLUT_Plotter* g);
        ~Tetris();
        
        //Main game function
        void Play(void);
        
    private:
        GLUT_Plotter* g;
        Screen* screen;
};

#endif /* TETRIS_H_ */
