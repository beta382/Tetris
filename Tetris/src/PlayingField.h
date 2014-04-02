/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#ifndef PLAYINGFIELD_H_
#define PLAYINGFIELD_H_

#include "Drawable.h"
#include "Tetromino.h"
#include "Shape.h"
#include "myVector.h"
#include "Block.h"

class PlayingField: public Drawable {
    public:
        PlayingField(GLUT_Plotter *g);
        PlayingField(GLUT_Plotter *g, int x, int y);
        PlayingField(GLUT_Plotter *g, int x, int y, int width, int height);
        PlayingField(const PlayingField&);
        PlayingField& operator =(const PlayingField&);
        ~PlayingField();
        
        Tetromino *spawnNewTetromino(TetrominoShape type);
        
        void merge(Shape *);
        
        bool canShiftDown(Shape *const) const;
        bool canShiftUp(Shape *const) const;
        bool canShiftLeft(Shape *const) const;
        bool canShiftRight(Shape *const) const;
        
        bool canRotateCW(Tetromino *const) const;
        bool canRotateCCW(Tetromino *const) const;
        
        /* ---------- Inherited from Drawable ---------- */
        void setLocation(int, int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        void init();
        bool couldAdd(Block *const) const;
        
        myVector<myVector<Block *> > blocks; // TODO: Make a better data structure
};

#endif /* PLAYINGFIELD_H_ */
