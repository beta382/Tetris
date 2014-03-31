/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Block.h"

Block::Block(): Drawable(0, 0, 1, 1) {}

Block::Block (int x, int y): Drawable(x, y, 1, 1) {}

/* ---------- Implemented from Drawable ---------- */

void Block::draw() {
    p.setColor(getColor());
    p.plot(getLocationX(), getLocationY(), SQUARE);
}

void Block::erase() {
    p.setColor(black);
    p.plot(getLocationX(), getLocationY(), SQUARE);
}
