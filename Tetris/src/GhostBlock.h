/*
 * GhostBlock.h
 *
 *  Created on: Apr 4, 2014
 *      Author: Austin
 */

#ifndef GHOSTBLOCK_H_
#define GHOSTBLOCK_H_

#include "Block.h"
#include "GLUT_Plotter.h"

class GhostBlock: public Block {
    public:
        GhostBlock(GLUT_Plotter *g);
        GhostBlock(GLUT_Plotter *g, int x, int y);
        GhostBlock(GLUT_Plotter *g, int x, int y, int size, int padding);
        GhostBlock(const GhostBlock&);
        GhostBlock& operator =(const GhostBlock&);
        ~GhostBlock();
        
        /* ---------- Inherited from Block ---------- */
        void doOnClear(myVector<myVector<Block *> > *);
        GhostBlock *makeNewClone(); // Covariant overload
        
        void draw();
        void erase();
};


#endif /* GHOSTBLOCK_H_ */
