/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "GLUT_Plotter.h"
#include "util.h"

#include <ctime>

/*
 * Drawable:
 *
 * Drawable is intended to be the abstract base class of all objects that are to be drawn to the
 *   screen. You MAY NOT independantly instantiate a Drawable object, this is enforced by making
 *   the constructors protected.
 */
class Drawable {
    public:
        /*
         * Draws this Drawable object to the screen. Must be implimented by children of Drawable.
         */
        virtual void draw() = 0;
        
        /*
         * Erases this Drawable object from the screen. Must be implimented by children of
         *   Drawable.
         */
        virtual void erase() = 0;
        
        
        /*
         * Assigns width the value of the passed parameter.
         * 
         * Parameters:
         *   int width: The value to assign to this Drawable object's width
         */
        void setWidth(int);
        
        /*
         * Getter for width.
         * 
         * Returns: The value of this Drawable object's width
         */
        int getWidth() const;
        
        /*
         * Assigns height the value of the passed parameter.
         * 
         * Parameters:
         *   int height: The value to assign to this Drawable object's height
         */
        void setHeight(int);
        
        /*
         * Getter for height.
         * 
         * Returns: The value of this Drawable object's height.
         */
        int getHeight() const;
        
        
        /*
         * Assigns x and y the values of the passed parameters.
         * 
         * Parameters:
         *   int x: The value to assign to this Drawable object's x
         *   int y: The value to assign to this Drawable object's y
         */
        virtual void setLocation(int, int);
        
        /*
         * Getter for x.
         * 
         * Returns: The value of this Drawable object's x.
         */
        int getLocationX() const;
        
        /*
         * Getter for y.
         * 
         * Returns: The value of this Drawable object's y.
         */
        int getLocationY() const;
        
        
        /*
         * Assigns foreground the value of the passed parameter.
         *  
         * Parameters:
         *   unsigned int color: The value to assign to this Drawable object's foreground
         */
        virtual void setForeground(unsigned int);
        
        /*
         * Getter for foreground.
         * 
         * Returns: The value of this Drawable object's foreground.
         */
        unsigned int getForeground() const;
        
        /*
         * Assigns background the value of the passed parameter.
         * 
         * Parameters:
         *   unsigned int color: The value to assign to this Drawable object's background
         */
        virtual void setBackground(unsigned int);
        
        /*
         * Getter for background.
         * 
         * Returns: The value of this Drawable object's background.
         */
        unsigned int getBackground() const;
        
        
        /*
         * Blinks this Drawable object. The final state will result in this Drawable object being
         *   erased.
         * 
         * Parameters:
         *   int times: The number of times to blink this Drawable object
         *   clock_t interval: The time in milliseconds between drawing and erasing this Drawable
         *     object
         */
        void blink(int, clock_t);

        /*
         * Assigns g the passed value. Should be called before using any Drawable objects.
         * 
         * Parameters:
         *   GLUT_Plotter* plotter: The value to assign to Drawable's static GLUT_Plotter* g
         */
        static void setG(GLUT_Plotter*);

        virtual ~Drawable() {}
    protected:
        
        /*
         * Instantiates a Drawable object using default values.
         */
        Drawable();
        
        /*
         * Instantiates a Drawable object using the passed parameters and other default values.
         * 
         * Parameters:
         *   int x: The value to initialize this Drawable object's x with
         *   int y: The value to initialize this Drawable object's y with
         */
        Drawable(int x, int y);
        
        /*
         * Instantiates a Drawable object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this Drawable object's x with
         *   int y: The value to initialize this Drawable object's y with
         *   int width: The value to initialize this Drawable object's width with
         *   int height: The value to initialize this Drawable object's height with
         *   unsigned int foreground: The value to initialize this Drawable object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this Drawable object's background
         *     with, defaults to Color::BLACK
         */
        Drawable(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        
        /*
         * Instantiates a Drawable object that is a copy of the passed Drawable object, except for
         *   bool isVisible, which is initialized with false.
         * 
         * Parameters:
         *   const Drawable& other: A reference to the Drawable object to copy from
         */
        Drawable(const Drawable&);
        
        /*
         * Assigns this Drawable object the values of the passed Drawable object, except for bool
         *   isVisible, which is assigned false.
         * 
         * Parameters:
         *   const Drawable& rhs: A reference to the Drawable object to assign from
         * 
         * Returns: A reference to this Drawable object
         */
        Drawable& operator =(const Drawable&);
        
        /*
         * These variables are intended to represent the x and y coordinates of the bottom-left
         *   corner of this Drawable object's bounding rectangle, however, they may be interpreted
         *   by sub-classes of Drawable in whatever manner best suits the nature of that object.
         */
        int x;
        int y;
        
        /*
         * These variables are intended to represent the width and height in pixels of this Drawable
         *   object's bounding rectangle, however, they may be interpreted by sub-classes of
         *   Drawable in whatever manner best suits the nature of that object.
         */
        int width;
        int height;
        
        /*
         * These variables are intended to represent the color of this Drawable object and the color
         *   of whatever lies behind this Drawable object, respectively.
         */
        unsigned int foreground;
        unsigned int background;
        
        /*
         * This variable is intended to represent whether or not this Drawable object is currently 
         *   visible on the screen. In implementations of draw() and erase(), this should be set
         *   accordingly, 
         */
        bool isVisible;

        /*
         * A shared GLUT_Plotter for all instances of objects that descend from Drawable. Should
         *   have a proper value assigned to it through Drawable::setG(GLUT_Plotter*) prior to 
         *   using a Drawable object.
         */
        static GLUT_Plotter* g;
};

#endif /* DRAWABLE_H_ */
