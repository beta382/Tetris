/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Block.h"

Block::Block(GLUT_Plotter *g): Drawable(g) {}

Block::Block (GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 1, 1) {}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    g->setColor(getColor());
    g->plot(getLocationX(), getLocationY());
}

void Block::erase() {
    g->setColor(Color::BLACK);
    g->plot(getLocationX(), getLocationY());
}
