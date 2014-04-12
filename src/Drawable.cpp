/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 28, 2014
 * Date last modified:     Apr 11, 2014
 */

#include "Drawable.h"

/*
 * A shared GLUT_Plotter for all instances of objects that descend from Drawable. Should have a
 *   proper value assigned to it through Drawable::setG(GLUT_Plotter) prior to using a Drawable
 *   object
 */
GLUT_Plotter *Drawable::g = NULL;

/*
 * Instantiates a Drawable object using default values
 * 
 * Initializes x, y, width, and height with 0
 * Initializes foreground with Color::WHITE
 * Initializes background with Color::BLACK
 * Initializes isVisible with false
 */
Drawable::Drawable(): 
        x(0), y(0), width(0), height(0), foreground(Color::WHITE), background(Color::BLACK),
          isVisible(false)
{
}

/*
 * Instantiates a Drawable object using the passed x and y values and other default values
 * 
 * Initializes x and y with the passed values
 * Initializes width and height with 0
 * Initializes foreground with Color::WHITE
 * Initializes background with Color::BLACK
 * Initializes isVisible with false
 */
Drawable::Drawable (int x, int y):
        x(x), y(y), width(0), height(0), foreground(Color::WHITE), background(Color::BLACK),
          isVisible(false)
{
}

/*
 * Instantiates a Drawable object using the passed values
 * 
 * Initializes x, y, width, height, foreground, and background with the passed values
 * Initializes isVisible with false
 */
Drawable::Drawable (int x, int y, int width, int height, unsigned int foreground, unsigned int background):
        x(x), y(y), width(width), height(height), foreground(foreground), background(background), isVisible(false)
{
}

/*
 * Instantiates a Drawable object that is a copy of the passed Drawable object
 * 
 * Initializes x, y, width, height, foreground, and background with the respective values from the 
 *   passed Drawable object
 * Initializes isVisible with false
 * 
 * Guaranteed that the passed Drawable object will not be modified
 */
Drawable::Drawable (const Drawable& other):
        x(other.x), y(other.y), width(other.width), height(other.height), foreground(other.foreground),
        background(other.background), isVisible(false)
{
}

/*
 * Assigns this Drawable object the values of the passed Drawable object
 * 
 * Assigns x, y, width, height, foreground, and background the respective values from the passed
 *   Drawable object
 * Assigns isVisible false
 * 
 * Guaranteed that the passed Drawable object will not be modified
 * 
 * Returns a reference to this Drawable object
 */
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

/*
 * Assigns width the passed value
 */
void Drawable::setWidth (int width) {
    this->width = width;
}

/*
 * Returns the value of width
 * 
 * Guaranteed that this Drawable object will not be modified
 */
int Drawable::getWidth () const {
    return width;
}

/*
 * Assigns height the passed value
 */
void Drawable::setHeight (int height) {
    this->height = height;
}

/*
 * Returns the value of height
 * 
 * Guaranteed that this Drawable object will not be modified
 */
int Drawable::getHeight () const {
    return height;
}

/*
 * Assigns x any y the passed values
 */
void Drawable::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

/*
 * Returns the value of x
 * 
 * Guaranteed that this Drawable object will not be modified
 */
int Drawable::getLocationX() const {
    return x;
}

/*
 * Returns the value of y
 * 
 * Guaranteed that this Drawable object will not be modified
 */
int Drawable::getLocationY() const {
    return y;
}

/*
 * Assigns foreground the passed value
 */
void Drawable::setForeground (unsigned int color) {
    foreground = color;
}

/*
 * Returns the value of foreground
 * 
 * Guaranteed that this Drawable object will not be modified
 */
unsigned int Drawable::getForeground() const {
    return foreground;
}

/*
 * Assigns background the passed value
 */
void Drawable::setBackground(unsigned int color) {
    background = color;
}

/*
 * Returns the value of background
 * 
 * Guaranteed that this Drawable object will not be modified
 */
unsigned int Drawable::getBackground() const {
    return background;
}

/*
 * Assigns g the passed value. Should be called before using any Drawable objects
 */
void Drawable::setG(GLUT_Plotter *plotter) {
	g = plotter;
}







