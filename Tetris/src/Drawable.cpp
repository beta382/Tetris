/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 28, 2014
 * Date last modified:     Mar 31, 2014
 */

#include "Drawable.h"

Drawable::Drawable(GLUT_Plotter *g) {
    this->g = g;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    color = Color::WHITE;
}

Drawable::Drawable (GLUT_Plotter *g, int x, int y) {
    this->g = g;
    this->x = x;
    this->y = y;
    width = 0;
    height = 0;
    color = Color::WHITE;
}

Drawable::Drawable (GLUT_Plotter *g, int x, int y, int width, int height, int color) {
    this->g = g;
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

void Drawable::setColor (unsigned int color) {
    this->color = color;
}

unsigned int Drawable::getColor() const {
    return color;
}











