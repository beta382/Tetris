/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef GHOSTBLOCK_H_
#define GHOSTBLOCK_H_

#include "Block.h"

/*
 * GhostBlock:
 *
 * Inherits from Block.
 *
 * GhostBlock is intended to represent a single block outline, to be used to show where a Block may end up. GhostBlock
 *   IS NOT intended to be inherited from.
 *
 * Functions overridden from Block:
 *     `void draw()`
 *     `void erase()`
 *     `GhostBlock *makeNewClone()`
 */

class GhostBlock: public Block {
    public:
        GhostBlock();
        GhostBlock(int x, int y);
        GhostBlock(int x, int y, int size, int padding);
        GhostBlock(const GhostBlock&);
        GhostBlock& operator =(const GhostBlock&);
        ~GhostBlock();
        
        /* ---------- Overriding from Block ---------- */
        void doOnClear(vector<vector<Block *> >&, int x, int y); // Only here to use a testing ground for future Blocks
        GhostBlock *makeNewClone(); // Covariant overload
        
        void draw();
        void erase();
};


#endif /* GHOSTBLOCK_H_ */
