/*
 * Author:                 Wes Cossick
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "Rectangle.h"

MyRectangle::MyRectangle (): Drawable(0, 0, 10, 10) {
    
}

MyRectangle::MyRectangle (int x, int y): Drawable(x, y, 10, 10) {
    
}

MyRectangle::MyRectangle (int x, int y, int width, int height, unsigned int foreground, unsigned int background):
        Drawable(x, y, width, height, foreground, background)
{
    
}

MyRectangle::MyRectangle (const MyRectangle& other): Drawable(other) {
    
}

MyRectangle& MyRectangle::operator =(const MyRectangle& rhs) {
    if (this != &rhs) {
        Drawable::operator =(rhs);
    }
    
    return *this;
}

MyRectangle::~MyRectangle() {
    erase();
}

int MyRectangle::getWidth() const {
    return width;
}

int MyRectangle::getHeight() const {
    return height;
}

/* ---------- Implemented from Drawable ---------- */

void MyRectangle::draw() {
    g->setColor(getForeground());
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

void MyRectangle::erase() {
    if (isVisible) {
        g->setColor(getBackground());
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
