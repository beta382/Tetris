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
 * All objects that directly inherit from Drawable MUST:
 *     Implement `void draw()`
 *     Implement `void erase()`
 *
 * All objects that directly inherit from Drawable MAY:
 *     Override `void setForeground(unsigned int)`
 *     Override `void setBackground(unsigned int)`
 *     Override `void setLocation(int, int)`
 *
 * Member data:
 *     `GLUT_Plotter *g`: Intended to be passed down
 *     `int x`/`int y`: Are intended to define the pixel-location of the bottom-left corner of the Drawable's bounding
 *         rectangle. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
 *     `int width`/`int height`: Are intended to define the number of pixels wide/tall the Drawable's bounding rectangle
 *         is. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
 *
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

        virtual ~Drawable() {};
    protected:
        Drawable(GLUT_Plotter *g);
        Drawable(GLUT_Plotter *g, int x, int y);
        Drawable(GLUT_Plotter *g, int x, int y, int width, int height, unsigned int foreground = Color::WHITE, 
                unsigned int background = Color::BLACK);
        Drawable(const Drawable&);
        virtual Drawable& operator =(const Drawable&);
        
        GLUT_Plotter *g;
        
        int x;
        int y;
        
        int width;
        int height;
        
        unsigned int foreground;
        unsigned int background;
        
        bool isVisible;
};

#endif /* DRAWABLE_H_ */
