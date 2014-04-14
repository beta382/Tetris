/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 12, 2014
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
 *   screen. You MAY NOT independantly instantiate a Drawable object, this is enforced by making the
 *   constructors protected.
 */

class Drawable {
    public:
        virtual void draw() = 0;
        virtual void erase() = 0;
        
        void setWidth(int);
        int getWidth() const;
        void setHeight(int);
        int getHeight() const;
        
        virtual void setLocation(int, int);
        int getLocationX() const;
        int getLocationY() const;
        
        virtual void setForeground(unsigned int);
        unsigned int getForeground() const;
        virtual void setBackground(unsigned int);
        unsigned int getBackground() const;
        
        void blink(int, int);

        static void setG(GLUT_Plotter *);

        virtual ~Drawable() {};
    protected:
        Drawable();
        Drawable(int x, int y);
        Drawable(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
        Drawable(const Drawable&);
        Drawable& operator =(const Drawable&);
        
        /*
         * These values are intended to represent the x and y coordinates of the bottom-left corner
         *   of this Drawable object's bounding rectangle, however, they may be interpreted by
         *   sub-classes of Drawable in whatever manner best suits the nature of that object.
         */
        int x;
        int y;
        
        /*
         * These values are intended to represent the width and height in pixels of this Drawable
         *   object's bounding rectangle, however, they may be interpreted by sub-classes of
         *   Drawable in whatever manner best suits the nature of that object.
         */
        int width;
        int height;
        
        /*
         * These values are intended to represent the color of this Drawable object and the color
         *   of whatever lies behind this Drawable object, respectively.
         */
        unsigned int foreground;
        unsigned int background;
        
        /*
         * This value is intended to represent whether or not this Drawable object is currently 
         *   visible on the screen. In implementations of draw() and erase(), this should be set
         *   accordingly, 
         */
        bool isVisible;

        static GLUT_Plotter *g;
};

#endif /* DRAWABLE_H_ */
