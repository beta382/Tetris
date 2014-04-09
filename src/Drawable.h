/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "GLUT_Plotter.h"
#include "drawkit.h"

#include <iostream>
#include <iomanip>

/*
 * Drawable:
 *
 * Drawable is intended to be the abstract base class of all objects that are to be drawn to the screen. You MAY NOT
 *   independantly instantiate a Drawable object, this is enforced by making the constructors protected.
 *
 * Constructors:
 *     `Drawable()`: Initializes `int x`, `int y`, `int width`, and `int height` to 0, `unsigned int foreground` to
 *       `Color::WHITE`, `unsigned int background` to `Color::BLACK`, and `bool isVisible` to false.
 *     `Drawable(int x, int y)`: Initializes `int x` and `int y` to the passed values, `int width`, and `int height` to
 *       0, `unsigned int foreground` to `Color::WHITE`, `unsigned int background` to `Color::BLACK`, and
 *       `bool isVisible` to false.
 *     `Drawable(int x, int y, int width, int height, unsigned int foreground, unsigned int background)`: Initializes
 *       `int x`, `int y`, `int width`, `int height`, `unsigned int foreground`, and `unsigned int background` to the
 *       passed values, and `bool isVisible` to false.
 *
 * Protected member data:
 *     `int x`/`int y`: Are intended to define the pixel-location of the bottom-left corner of the Drawable's bounding
 *       rectangle. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
 *     `int width`/`int height`: Are intended to define the number of pixels wide/tall the Drawable's bounding rectangle
 *       is. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
 *     `unsigned int foreground`/`unsigned int background`: Are intended to define the foreground color and background
 *       color of the Drawable. Descendants of Drawable MAY define and interpret these values however best suits its
 *       purpose.
 *     `bool isVisible`: Is intended to define whether or not the Drawable is visible on the screen. It is STRONGLY
 *       ENCOURAGED that you use this as a check when implementing `void erase()`, and that you set it accordingly
 *       at the end of your `void draw()` and `void erase()` implementations. It is STRONGLY ENCOURAGED that you NOT use
 *       this in a different manner than described.
 *
 * Protected static data:
 *     `GLUT_Plotter *g`: A shared GLUT_Plotter for all instances of objects that descend from Drawable.
 *
 * Public functions:
 *     `void setWidth(int)`/`int getWidth()`/`void setHeight(int)`/`int getHeight()`: Simple getters and setters for
 *       `int width` and `int height`.
 *     `void setLocation(int, int)`/`int getLocationX()`/`int getLocationY()`: Simple getters and setters for `int x`
 *       and `int y`.
 *     `void setForeground(unsigned int)`/`unsigned int getForeground()`/`void setBackground(unsigned int)`/`unsigned
 *       int getBackground()`: Simple getters and setters for `unsigned int foreground` and `unsigned int background`.
 *     `void draw()`/`void erase()`: Pure virtual functions that MUST be implemented by descendants of Drawable to draw
 *       and erase the Drawable on the screen.
 *
 * All objects that directly inherit from Drawable MUST:
 *     Implement `void draw()`
 *     Implement `void erase()`
 *
 * All objects that directly or indirectly inherit from Drawable MAY:
 *     Override `void setForeground(unsigned int)`
 *     Override `void setBackground(unsigned int)`
 *     Override `void setLocation(int, int)`
 *
 * All objects that directly or indirectly inherit from Drawable are STRONGLY ENGOURAGED to:
 *     Define a proper copy constructor that calls `Drawable(const Drawable&)`, even if there is no memory management
 *     Define a proper assignment operator that calls `Drawable::operator =(const Drawable&)`, even if there is not
 *       memory management
 * (This is because each new Drawable, even if it is a copy, should have `bool isVisible` set to false regardless of its
 *   origin)
 */

class Drawable {
    public:
        virtual void draw() = 0;
        virtual void erase() = 0;
        
        void setWidth(int);
        int getWidth() const;
        void setHeight(int);
        int getHeight() const;
        
        virtual void setLocation(int x, int y);
        int getLocationX() const;
        int getLocationY() const;
        
        virtual void setForeground(unsigned int color);
        unsigned int getForeground() const;
        virtual void setBackground(unsigned int color);
        unsigned int getBackground();

        static void setG(GLUT_Plotter *);

        virtual ~Drawable() {};
    protected:
        Drawable();
        Drawable(int x, int y);
        Drawable(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        Drawable(const Drawable&);
        Drawable& operator =(const Drawable&);
        
        int x;
        int y;
        
        int width;
        int height;
        
        unsigned int foreground;
        unsigned int background;
        
        bool isVisible;

        static GLUT_Plotter *g;
};

#endif /* DRAWABLE_H_ */
