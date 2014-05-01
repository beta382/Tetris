/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "Rect.h"

Rect::Rect ():
Drawable(0, 0, 10, 10)
{ 
}

Rect::Rect (int x, int y):
Drawable(x, y, 10, 10)
{
}

Rect::Rect (int x, int y, int width, int height, unsigned int foreground, 
        unsigned int background):
Drawable(x, y, width, height, foreground, background)
{
}

Rect::Rect (const Rect& other):
Drawable(other)
{
}

Rect& Rect::operator =(const Rect& rhs) {
    if (this != &rhs) {
        Drawable::operator =(rhs);
    }
    
    return *this;
}

Rect::~Rect() {
    erase();
}

int Rect::getWidth() const {
    return width;
}

int Rect::getHeight() const {
    return height;
}

/* ---------- Implemented from Drawable ---------- */

void Rect::draw() {
    g->setColor(getForeground());
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (getLocationX()+i >= 0 && getLocationX()+i < g->getWidth() && 
                    getLocationY()+j >= 0 && getLocationY()+j < g->getHeight()) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}

void Rect::erase() {
    if (isVisible) {
        g->setColor(getBackground());
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (getLocationX()+i >= 0 && getLocationX()+i < g->getWidth() && 
                        getLocationY()+j >= 0 && getLocationY()+j < g->getHeight()) {
                    g->plot(getLocationX()+i, getLocationY()+j);
                }
            }
        }

        isVisible = false;
    }
}
