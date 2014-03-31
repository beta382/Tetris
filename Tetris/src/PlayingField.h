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
        PlayingField();
        PlayingField(int x, int y, int width, int height);
        ~PlayingField();
        
        Tetromino *spawnNewTetromino(int x, int y, TetrominoShape type);
        
        void merge(Shape *);
        
        bool canShiftDown(Shape *) const;
        bool canShiftUp(Shape *) const;
        bool canShiftLeft(Shape *) const;
        bool canShiftRight(Shape *) const;
        
        bool canRotateCW(Tetromino *) const;
        bool canRotateCCW(Tetromino *) const;
        
        /* ---------- Inherited from Drawable ---------- */
        void setLocation(int, int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        myVector<myVector<Block *> > blocks;
};

#endif /* PLAYINGFIELD_H_ */
