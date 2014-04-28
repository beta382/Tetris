/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 28, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "Drawable.h"

/*
 * A shared GLUT_Plotter for all instances of objects that descend from Drawable. Should have a
 *   proper value assigned to it through Drawable::setG(GLUT_Plotter*) prior to using a Drawable
 *   object.
 */
GLUT_Plotter* Drawable::g = NULL;

/* ---------- Protected Constructors/Destructor ---------- */

/*
 * Instantiates a Drawable object using default values.
 */
Drawable::Drawable(): 
        x(0), y(0), width(0), height(0), foreground(Color::WHITE), background(Color::BLACK),
        isVisible(false)
{
}

/*
 * Instantiates a Drawable object using the passed parameters and other default values.
 * 
 * Parameters:
 *   int x: The value to initialize this Drawable object's x with
 *   int y: The value to initialize this Drawable object's y with
 */
Drawable::Drawable (int x, int y):
        x(x), y(y), width(0), height(0), foreground(Color::WHITE), background(Color::BLACK),
        isVisible(false)
{
}

/*
 * Instantiates a Drawable object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this Drawable object's x with
 *   int y: The value to initialize this Drawable object's y with
 *   int width: The value to initialize this Drawable object's width with
 *   int height: The value to initialize this Drawable object's height with
 *   unsigned int foreground: The value to initialize this Drawable object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this Drawable object's background with,
 *     defaults to Color::BLACK
 */
Drawable::Drawable (int x, int y, int width, int height, unsigned int foreground,
  unsigned int background):
        x(x), y(y), width(width), height(height), foreground(foreground), background(background),
        isVisible(false)
{
}

/*
 * Instantiates a Drawable object that is a copy of the passed Drawable object, except for bool
 *   isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const Drawable& other: A reference to the Drawable object to copy from
 */
Drawable::Drawable (const Drawable& other):
        x(other.x), y(other.y), width(other.width), height(other.height),
        foreground(other.foreground), background(other.background), isVisible(false)
{
}


/* ---------- Public ---------- */

/*
 * Assigns width the value of the passed parameter.
 * 
 * Parameters:
 *   int width: The value to assign to this Drawable object's width
 */
void Drawable::setWidth (int width) {
    this->width = width;
}

/*
 * Getter for width.
 * 
 * Returns: The value of this Drawable object's width
 */
int Drawable::getWidth () const {
    return width;
}

/*
 * Assigns height the value of the passed parameter.
 * 
 * Parameters:
 *   int height: The value to assign to this Drawable object's height
 */
void Drawable::setHeight (int height) {
    this->height = height;
}

/*
 * Getter for height.
 * 
 * Returns: The value of this Drawable object's height.
 */
int Drawable::getHeight () const {
    return height;
}

/*
 * Assigns x and y the values of the passed parameters.
 * 
 * Parameters:
 *   int x: The value to assign to this Drawable object's x
 *   int y: The value to assign to this Drawable object's y
 */
void Drawable::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

/*
 * Getter for x.
 * 
 * Returns: The value of this Drawable object's x.
 */
int Drawable::getLocationX() const {
    return x;
}

/*
 * Getter for y.
 * 
 * Returns: The value of this Drawable object's y.
 */
int Drawable::getLocationY() const {
    return y;
}

/*
 * Assigns foreground the value of the passed parameter.
 *  
 * Parameters:
 *   unsigned int color: The value to assign to this Drawable object's foreground
 */
void Drawable::setForeground (unsigned int color) {
    foreground = color;
}

/*
 * Getter for foreground.
 * 
 * Returns: The value of this Drawable object's foreground.
 */
unsigned int Drawable::getForeground() const {
    return foreground;
}

/*
 * Assigns background the value of the passed parameter.
 * 
 * Parameters:
 *   unsigned int color: The value to assign to this Drawable object's background
 */
void Drawable::setBackground(unsigned int color) {
    background = color;
}

/*
 * Getter for background.
 * 
 * Returns: The value of this Drawable object's background.
 */
unsigned int Drawable::getBackground() const {
    return background;
}

/*
 * Blinks this Drawable object. The final state will result in this Drawable object being erased.
 * 
 * Parameters:
 *   int times: The number of times to blink this Drawable object
 *   clock_t interval: The time in milliseconds between drawing and erasing this Drawable object
 */
void Drawable::blink(int times, clock_t interval) {
    for (int r = 0; r < times; r++) {
        
        draw();
        util::wait(interval, g);
        
        erase();
        util::wait(interval, g);
    }
}


/* ---------- Protected ---------- */

/*
 * Assigns this Drawable object the values of the passed Drawable object, except for bool isVisible,
 *   which is assigned false.
 * 
 * Parameters:
 *   const Drawable& rhs: A reference to the Drawable object to assign from
 * 
 * Returns: A reference to this Drawable object
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


/* ---------- Static ---------- */

/*
 * Assigns g the passed value. Should be called before using any Drawable objects.
 * 
 * Parameters:
 *   GLUT_Plotter* plotter: The value to assign to Drawable's static GLUT_Plotter* g
 */
void Drawable::setG(GLUT_Plotter* plotter) {
    g = plotter;
}
