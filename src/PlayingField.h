/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef PLAYINGFIELD_H_
#define PLAYINGFIELD_H_

#include "Drawable.h"
#include "Tetromino.h"
#include "Shape.h"
#include <vector>
#include "drawkit.h"
#include "Rectangle.h"

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
 * Private member data:
 *    `vector<vector<Block *> > blocks`: A two-dimensional array of pointers to dynamically allocated Blocks,
 *      representing the Blocks currently on the field. The index of the Block DOES directly correlate to its on-screen
 *      location. Entries that don't contain a Block address will contain NULL.
 *    `MyRectangle *bgRect`: A rectangle fill representing the background of the playing field.
 *    `int blockSize`/`int padding`: The size of the Blocks and padding between Blocks.
 *
 * Public functions:
 *     `Tetromino<BlockType> *spawnNewTetromino(TetrominoShape)`: Allocates a new Tetromino<BlockType> with the
 *       specified shape and BlockType within the block field, and returns the address of the allocated
 *       Tetromino<BlockType>.
 *     `void mergeAndDelete(Shape *)`: Merges a copy of the Shape into the block field, and then de-allocates the Shape.
 *     `bool canShiftUp(Shape *)`/`bool canShiftDown(Shape *)`/`bool canShiftLeft(Shape *)`/`bool
 *       canShiftRight(Shape *)`: Determines whether or not the specified Shape can shift in the respective direction
 *       within the block field, without actually shifting the Shape.
 *     `bool canRotateCW(TetrominoBase *)`/`bool canRotateCCW(TetrominoBase *)`: Determines whether or not the specified
 *       TetrominoBase can rotate in the respective direction within the block field, without actually rotating the
 *       TetrominoBase.
 *
 * Private functions:
 *     `void init()`: Initializes member data, draws the initial state to the screen.
 *     `bool couldAdd(Block *)`: Determines whether or not the specified Block could be added to the block field without
 *       conflict.
 *     `void doLineClear()`: Determines whether or not there needs to occur a line clear, and if so, performs the line
 *       clear.
 *     `vector<Shape *> formShapes()`: Disassembles the block field and groups contiguous groups of Blocks into distinct
 *       Shapes, returning those Shapes. After running this, `vector<vector<Block *> > blocks` will be entirely NULL.
 *     `void makeShapeRecursively(Shape *, int, int)`: Starting at the specified location in the block field, adds
 *       adjacent blocks to the Shape until all contiguous Blocks are added to the Shape.
 *
 * Functions implimented from Drawable:
 *     `void draw()`
 *     `void erase()`
 *
 * Functions overridden from Drawable:
 *     `void SetLocation(int, int)`
 *
 */

const int BLOCK_SIZE = 15;
const int BLOCK_PADDING = 2;

class PlayingField: public Drawable {
    public:
        PlayingField();
        PlayingField(int x, int y);
        PlayingField(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        PlayingField(const PlayingField&);
        PlayingField& operator =(const PlayingField&);
        ~PlayingField();
        
        template <typename BlockType>
        Tetromino<BlockType> *spawnNewTetromino(TetrominoShape type);
        
        void mergeAndDelete(Shape *);

        bool canShiftUp(Shape *const) const;
        bool canShiftDown(Shape *const) const;
        bool canShiftLeft(Shape *const) const;
        bool canShiftRight(Shape *const) const;
        
        bool canRotateCW(TetrominoBase *const) const;
        bool canRotateCCW(TetrominoBase *const) const;
        
        /* ---------- Overriding from Drawable ---------- */
        void setLocation(int, int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    private:
        void init();
        bool couldAdd(Block *const) const;
        
        void doLineClear();
        vector<Shape *> formShapes();
        void makeShapeRecursively(Shape *, int x, int y);
        
        MyRectangle *bgRect;
        
        vector<vector<Block *> > blocks; // TODO: Make a better data structure, or are we allowed to use STL?
};

/* ---------- spawnNewTetromino method template implementation ---------- */

template <typename BlockType>
Tetromino<BlockType> *PlayingField::spawnNewTetromino (TetrominoShape type) {
    Tetromino<BlockType> *tetromino = new Tetromino<BlockType>(getLocationX()+(BLOCK_SIZE+BLOCK_PADDING)*(getWidth()/2),
            getLocationY()+(BLOCK_SIZE+BLOCK_PADDING)*getHeight(), BLOCK_SIZE, BLOCK_PADDING, type, getForeground());
    
    // We spawn right above the field, this puts us at the top of the screen, properly centered
    tetromino->setLocation(tetromino->getLocationX()-tetromino->getTotalBlockSize()*((tetromino->getWidth()+1)/2),
            tetromino->getLocationY()-tetromino->getTotalBlockSize()*tetromino->getHeight());
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    // Probably return NULL if we can't spawn period, which would special-case a "game over"
    
    return tetromino;
}

#endif /* PLAYINGFIELD_H_ */
