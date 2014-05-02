/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 26, 2014
 */

#ifndef RECT_H_
#define RECT_H_

#include "Drawable.h"

class Rect: public Drawable {
_registerForLeakcheckWithID(Rect)
    public:
        Rect();
        Rect(int x, int y);
        Rect(int x, int y, int width, int height, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
        Rect(const Rect&);
        Rect& operator =(const Rect&);
        ~Rect();
        
        int getWidth() const;
        int getHeight() const;
        
        /* ---------- Implemented from Drawable ---------- */
        void draw();
        void erase();
};

#endif /* RECT_H_ */
