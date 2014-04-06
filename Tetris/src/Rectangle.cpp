/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include "Rectangle.h"

Rectangle::Rectangle (GLUT_Plotter *g): Drawable(g, 0, 0, 10, 10) {
    padding = 0;
}

Rectangle::Rectangle (GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 10, 10) {
    padding = 0;
}

Rectangle::Rectangle (GLUT_Plotter *g, int x, int y, int size, int padding): Drawable(g, x, y, size, size) {
    this->padding = padding;
}

Rectangle::Rectangle (const Rectangle& other): Drawable(other) {
    padding = other.padding;
}

Rectangle& Rectangle::operator =(const Rectangle& rhs) {
    if (this != &rhs) {
        Drawable::operator =(rhs);
        padding = rhs.padding;
    }
    
    return *this;
}

Rectangle::~Rectangle() {
    erase();
}

int Rectangle::getSize() const {
    return width;
}

int Rectangle::getPadding() const {
    return padding;
}

int Rectangle::getTotalSize() const {
    return getSize()+getPadding();
}

void Rectangle::doOnClear(myVector<myVector<Rectangle *> >& blockField) {
    // Do nothing
}

Rectangle *Rectangle::makeNewClone() {
    return new Rectangle(*this);
}

/* ---------- Implemented from Drawable ---------- */

void Rectangle::draw() {
    g->setColor(getColor());
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

void Rectangle::erase() {
    if (isVisible) {
        g->setColor(Color::BLACK);
        for (int i = 0; i < getSize(); i++) {
            for (int j = 0; j < getSize(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
