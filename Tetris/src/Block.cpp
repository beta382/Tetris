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

Block::~Block() {
    erase();
}

int Block::getSize() const {
    return width;
}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    g->setColor(getColor());
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
}

void Block::erase() {
    g->setColor(Color::BLACK);
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
}
