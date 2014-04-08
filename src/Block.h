/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "Drawable.h"
#include <vector>

/*
 * Block:
 *
 * Inherits from Drawable.
 *
 * Block is intended to represent a single block, and define behaviors specific to that block. Block IS intended to be
 *   inherited from.
 *
 * Protected member data:
 *    `int padding`: The padding the Block should have in addition to it's visible representation. Specifically, defines
 *      the number of pixels above and to the right the Block technically occupies, but not visibly.
 *
 * Public functions:
 *     `int getSize()`/`int getPadding()`/`int getTotalSize()`: Getters for `int width`, `int padding`, and the sum
 *       of both.
 *     `void doOnClear(vector<vector<Bock *> >&, int, int)`: Defines what special effect should happen to the given
 *       block field at the given index when the Block is cleared.
 *     `void Block *makeNewClone()`: Allows for proper copying of a Block or one of its descendants into a polymorphic
 *       Block pointer without knowing whether the object being copied is a Block or one of its descendants. This MUST
 *       be properly overridden by all descendants of Block.
 *
 * Functions implimented from Drawable:
 *     `void draw()`
 *     `void erase()`
 *
 * All objects that directly or indirectly inherit from Block MAY:
 *     Override `void doOnClear(vector<vector<Bock *> >&, int, int)`
 *
 * All objects that directly or indirectly inherit from Block MUST:
 *     Override `Block *makeNewClone();`
 */

class Block: public Drawable {
    public:
        Block();
        Block(int x, int y);
        Block(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        Block(const Block&);
        Block& operator =(const Block&);
        ~Block();
        
        int getSize() const;
        int getPadding() const;
        int getTotalSize() const;
        
        virtual void doOnClear(vector<vector<Block *> >&, int x, int y);
        virtual Block *makeNewClone();
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        int padding;
};

#endif /* BLOCK_H_ */
