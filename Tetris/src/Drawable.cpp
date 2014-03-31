/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 28, 2014
 * Date last modified:     Mar 28, 2014
 */

#include "Drawable.h"

Drawable::Drawable() {
    x = 0;
    y = 0;
    width = 1;
    height = 1;
    color = white;
}

Drawable::Drawable (int x, int y, int width, int height, ink color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

void Drawable::setWidth (int width) {
    this->width = width;
}

int Drawable::getWidth () const {
    return width;
}

void Drawable::setHeight (int height) {
    this->height = height;
}

int Drawable::getHeight () const {
    return height;
}

void Drawable::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

int Drawable::getLocationX() const {
    return x;
}

int Drawable::getLocationY() const {
    return y;
}

void Drawable::setColor (ink color) {
    this->color = color;
}

ink Drawable::getColor() const {
    return color;
}











