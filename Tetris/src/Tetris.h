/*
 * Tetris.h - Tetris game class header
 *
 *  Created on: Mar 28, 2014
 *  Created on: Mar 28, 2014
 *      Author: Dr. Booth
 */

#ifndef TETRIS_H_
#define TETRIS_H_

#include "Drawable.h"
#include "PlayingField.h"
#include "Tetris.h"

#include <cstdlib>
#include <ctime>

class Tetris: public Drawable {
    public:
        //constructor
        Tetris(GLUT_Plotter *g);
        Tetris(GLUT_Plotter *g, int x, int y);
        ~Tetris();
        // TODO Copy constructors EVERYWHERE, etc, cause even though I probably won't use them, gotta make Booth happy
        
        //Main game function
        void Play(void);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        void init();
        
        PlayingField *field;
        Tetromino *currentTetromino;
};

#endif /* TETRIS_H_ */
