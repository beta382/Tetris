/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Drawable.h"
#include "myVector.h"

class Rectangle: public Drawable {
    public:
        Rectangle(GLUT_Plotter *g);
        Rectangle(GLUT_Plotter *g, int x, int y);
        Rectangle(GLUT_Plotter *g, int x, int y, int size, int padding);
        Rectangle(const Rectangle&);
        Rectangle& operator =(const Rectangle&);
        ~Rectangle();
        
        int getSize() const;
        int getPadding() const;
        int getTotalSize() const;
        
        virtual void doOnClear(myVector<myVector<Rectangle *> >&);
        virtual Rectangle *makeNewClone();
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
    protected:
        int padding;
};

#endif /* RECTANGLE_H_ */
