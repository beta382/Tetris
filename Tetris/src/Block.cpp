/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Block.h"

Block::Block (GLUT_Plotter *g): Drawable(g, 0, 0, 10, 10) {}

Block::Block (GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 10, 10) {}

Block::Block (GLUT_Plotter *g, int x, int y, int size): Drawable(g, x, y, size, size) {}

Block::Block (const Block& other): Drawable(other.g, other.x, other.y, other.getSide(), other.getSide(), other.color) {}

Block::~Block() {
    erase();
}

int Block::getSide() const {
    return width;
}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    g->setColor(getColor());
    for (int i = 0; i < getSide(); i++) {
        for (int j = 0; j < getSide(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

void Block::erase() {
    if (isVisible) {
        g->setColor(Color::BLACK);
        for (int i = 0; i < getSide(); i++) {
            for (int j = 0; j < getSide(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
