/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "Drawable.h"
#include <vector>

class Block: public Drawable {
    public:
        Block(GLUT_Plotter *g);
        Block(GLUT_Plotter *g, int x, int y);
        Block(GLUT_Plotter *g, int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
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
