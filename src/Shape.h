/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 30, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Drawable.h"
#include <vector>
#include "Block.h"

/*
 * Shape:
 *
 * Inherits from Drawable.
 *
 * Shape is intended to represent and be a wrapper for a collection of Blocks, and provide methods for interfacing with
 *   and manipulating the Blocks. Shape IS intended to be inherited from.
 *
 * Protected member data:
 *    `vector<Block *> blocks`: An array of pointers to dynamically allocated Blocks, representing the Blocks contained
 *      within the Shape. The index of the Block DOES NOT correlate to its on-screen location.
 *    `int blockSize`/`int padding`: The size of the Blocks and padding between Blocks.
 *
 * Public functions:
 *     `Block *getBlock(int)`: Gets the Block pointer at the specified index.
 *     `int numBlocks()`: Returns the number of Blocks the Shape contains.
 *     `int getBlockSize()`/`int getPadding()`/`int getTotalBlockSize()`: Getters for `int blockSize`, `int padding`,
 *       and the sum of both.
 *     `void shiftUp()`/`void shiftDown()`/`void shiftLeft()`/`void shiftRight()`: Shifts the Shape one block in the
 *       respective direction, without performing checks. Within the context of a PlayingField, should be surrounded
 *       with a conditional.
 *     `Shape& addBlock(Block *)`: Adds the Block pointer to the Shape, and returns the Shape by reference for chaining.
 *
 * Functions implimented from Drawable:
 *     `void draw()`
 *     `void erase()`
 *
 * Functions overridden from Drawable:
 *     `void setLocation(int, int)`
 *     `void setBackground(unsigned int)`
 *     `void setForeground(unsigned int)`
 */

class Shape: public Drawable {
    public:
        Shape();
        Shape(int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);
        Shape(const Shape&);
        Shape& operator =(const Shape&);
        ~Shape();
        
        Block *getBlock(int) const;
        int numBlocks() const;
        
        int getBlockSize() const;
        int getPadding() const;
        int getTotalBlockSize() const;
        
        void shiftUp();
        void shiftDown();
        void shiftLeft();
        void shiftRight();
        
        Shape& addBlock(Block *const);
        
        /* ---------- Overriding from Drawable ---------- */
        void setLocation(int, int);
        void setForeground (unsigned int);
        void setBackground (unsigned int);
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        vector<Block *> blocks;
        
        int blockSize;
        int padding;
};

#endif /* SHAPE_H_ */
