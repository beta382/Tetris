/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 12, 2014
 */

#ifndef PLAYINGFIELD_H_
#define PLAYINGFIELD_H_

#include "Drawable.h"
#include "Tetromino.h"
#include "Shape.h"
#include "Rectangle.h"

#include <vector>
#include <algorithm>
#include <ctime>

/*
 * PlayingField:
 *
 * Inherits from Drawable.
 *
 * PlayingField is intended to represent the field of blocks in play, and provide methods for general core gameplay,
 *   including generating and merging tetrominos and checking whether or not a shape can move or rotate within the block
 *   field. PlayingField IS NOT intended to be inherited from.
 *
 * PlayingField defines and interprets `int width` and `int height` as the number of Blocks wide and tall the block
 *   field is.
 */

class PlayingField: public Drawable {
    public:
        PlayingField();
        PlayingField(int x, int y, int width, int height, int blockSize, int padding,
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK);
        PlayingField(const PlayingField&);
        PlayingField& operator =(const PlayingField&);
        ~PlayingField();
        
        template <typename BlockType>
        Tetromino<BlockType> *spawnNewTetromino(TetrominoShape type) const;
        
        void mergeAndDelete(Shape *);

        bool canShiftUp(const Shape *) const;
        bool canShiftDown(const Shape *) const;
        bool canShiftLeft(const Shape *) const;
        bool canShiftRight(const Shape *) const;
        
        bool canRotateCW(const TetrominoBase *) const;
        bool canRotateCCW(const TetrominoBase *) const;
        
        /* ---------- Overriding from Drawable ---------- */
        void setLocation(int, int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        bool couldAdd(const Block *) const;
        
        void doLineClear(vector<int>);
        vector<int> getClearableLines();
        void normalizeBlocks(Shape&);
        void doClearedBlockEffects(Shape&, vector<Shape *>&);
        void doFall(vector<Shape *>&);
        vector<Shape *> formNewContiguousShapes(vector<vector<Block *> >&);
        void r_makeContiguousShape(Shape *, int, int, vector<vector<Block *> >&);
        void mergeCopy(const Shape *);
        
        int xIndexFromLocation(const Block *) const;
        int yIndexFromLocation(const Block *) const;
        int blockSize;
        int padding;
        
        MyRectangle bgRect;
        
        vector<vector<Block *> > blockField;
};

/* ---------- spawnNewTetromino method template implementation ---------- */

/*
 * Dynamically allocates a Tetromino<BlockType> with the passed TetrominoShape centered at the top 
 *   of the block field
 * 
 * Returns a pointer to the dynamically allocated Tetromino<BlockType>, or NULL if the tetromino
 *   cannot be spawned
 * 
 * Guaranteed that this PlayingField object will not be modified
 */
template <typename BlockType>
Tetromino<BlockType> *PlayingField::spawnNewTetromino (TetrominoShape type) const {
    Tetromino<BlockType> *tetromino = new Tetromino<BlockType>(getLocationX()+(blockSize+padding)*(getWidth()/2),
            getLocationY()+(blockSize+padding)*getHeight(), blockSize, padding, type, getForeground());
    
    // We spawn right above the field, this puts us at the top of the screen, properly centered
    tetromino->setLocation(tetromino->getLocationX()-tetromino->getTotalBlockSize()*((tetromino->getWidth()+1)/2),
            tetromino->getLocationY()-tetromino->getTotalBlockSize()*tetromino->getHeight());
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    // Probably return NULL if we can't spawn period, which would special-case a "game over"
    
    return tetromino;
}

#endif /* PLAYINGFIELD_H_ */
