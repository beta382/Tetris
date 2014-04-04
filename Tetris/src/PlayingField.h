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
#include "Blocks.h"

const int BLOCK_SIZE = 15;
const int BLOCK_PADDING = 2;

class PlayingField: public Drawable {
    public:
        PlayingField(GLUT_Plotter *g);
        PlayingField(GLUT_Plotter *g, int x, int y);
        PlayingField(GLUT_Plotter *g, int x, int y, int width, int height);
        PlayingField(const PlayingField&);
        PlayingField& operator =(const PlayingField&);
        ~PlayingField();
        
        template <typename BlockType>
        Tetromino<BlockType> *spawnNewTetromino(TetrominoShape type);
        
        void merge(Shape *);
        
        bool canShiftDown(Shape *const) const;
        bool canShiftUp(Shape *const) const;
        bool canShiftLeft(Shape *const) const;
        bool canShiftRight(Shape *const) const;
        
        bool canRotateCW(TetrominoBase *const) const;
        bool canRotateCCW(TetrominoBase *const) const;
        
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

template <typename BlockType>
Tetromino<BlockType> *PlayingField::spawnNewTetromino (TetrominoShape type) {
    Tetromino<BlockType> *tetromino = new Tetromino<BlockType>(g, getLocationX()+(BLOCK_SIZE+BLOCK_PADDING)*(getWidth()/2), 
            getLocationY()+(BLOCK_SIZE+BLOCK_PADDING)*getHeight(), BLOCK_SIZE, BLOCK_PADDING, type);
    
    // We spawn right above the field, this puts us at the top of the screen, properly centered
    tetromino->setLocation(tetromino->getLocationX()-tetromino->getTotalBlockSize()*((tetromino->getWidth()+1)/2),
            tetromino->getLocationY()-tetromino->getTotalBlockSize()*tetromino->getHeight());
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    // Probably return NULL if we can't spawn period, which would special-case a "game over"
    
    return tetromino;
}

#endif /* PLAYINGFIELD_H_ */
