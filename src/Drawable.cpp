/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 28, 2014
 * Date last modified:     Apr  8, 2014
 */

#include "Drawable.h"

GLUT_Plotter *Drawable::g = NULL;

Drawable::Drawable() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    foreground = Color::WHITE;
    background = Color::BLACK;
    isVisible = false;
}

Drawable::Drawable (int x, int y) {
    this->x = x;
    this->y = y;
    width = 0;
    height = 0;
    foreground = Color::WHITE;
    background = Color::BLACK;
    isVisible = false;
}

Drawable::Drawable (int x, int y, int width, int height, unsigned int foreground, unsigned int background) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->foreground = foreground;
    this->background = background;
    isVisible = false;
}

Drawable::Drawable (const Drawable& other) {
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
    foreground = other.foreground;
    background = other.background;
    isVisible = false;
}

Drawable& Drawable::operator =(const Drawable& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        width = rhs.width;
        height = rhs.height;
        foreground = rhs.foreground;
        background = rhs.background;
        isVisible = false;
    }
    
    return *this;
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

void Drawable::setForeground (unsigned int color) {
    foreground = color;
}

unsigned int Drawable::getForeground() const {
    return foreground;
}

void Drawable::setBackground(unsigned int color) {
    background = color;
}

unsigned int Drawable::getBackground() {
    return background;
}

void Drawable::setG(GLUT_Plotter *plotter) {
	g = plotter;
}







