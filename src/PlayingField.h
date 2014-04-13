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
 *
 * Constructors:
 *     `PlayingField()`: Calls `Drawable(0, 0, 10, 20)`, initializes `int blockSize` to 10 and `int padding` to 0, then
 *       calls `void init()`.
 *     `PlayingField(int x, int y, int width, int height, int blockSize, int padding, unsigned int foreground,
 *       unsigned int background)`: Calls `Drawable(x, y, width, height, foreground, background)`, initializes
 *       `int blockSize` and `int padding` to the passed values, then calls `void init()`.
 *
 * Private member data:
 *     `vector<vector<Block *> > blocks`: A two-dimensional array of pointers to dynamically allocated Blocks,
 *       representing the Blocks currently on the field. The index of the Block DOES directly correlate to its on-screen
 *       location. Entries that don't contain a Block address will contain NULL.
 *     `MyRectangle *bgRect`: A rectangle fill representing the background of the playing field.
 *     `int blockSize`/`int padding`: The size of the Blocks and padding between Blocks.
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
 * Functions implemented from Drawable:
 *     `void draw()`
 *     `void erase()`
 *
 * Functions overridden from Drawable:
 *     `void SetLocation(int, int)`
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
        
        void doLineClear();
        vector<int> getClearableLines();
        void normalizeBlocks(Shape&);
        void doClearedBlockEffects(Shape&, vector<Shape *>&);
        vector<Shape *> formShapes(vector<vector<Block *> >&);
        void makeShapeRecursively(Shape *, int, int, vector<vector<Block *> >&);
        void merge(const Shape *);
        
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
