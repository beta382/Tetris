/*
 * Tetris.h - Tetris game class header
 *
 *  Created on: Mar 28, 2014
 *  Created on: Mar 28, 2014
 *      Author: Dr. Booth
 */

#ifndef TETRIS_H_
#define TETRIS_H_

#include "GLUT_Plotter.h"
#include "Game.h"
#include "util.h"

class Tetris {
    public:
        //constructor
        Tetris(GLUT_Plotter *g);
        ~Tetris();
        
        //Main game function
        void Play(void);
        
    private:
        GLUT_Plotter *g;
        Screen *screen;
};

#endif /* TETRIS_H_ */
