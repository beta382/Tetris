/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Rectangle.h"

MyRectangle::MyRectangle (): Drawable(0, 0, 10, 10) {
    
}

MyRectangle::MyRectangle (int x, int y): Drawable(x, y, 10, 10) {
    
}

MyRectangle::MyRectangle (int x, int y, int width, int height, int color): Drawable(x, y, width, height, color)
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
        g->setColor(Color::BLACK);
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}