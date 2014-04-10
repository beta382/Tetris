/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 10, 2014
 * Date last modified:     Apr 10, 2014
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "Drawable.h"

class Screen: public Drawable {
    public:
        virtual void respondToKey(int) = 0;
        virtual void respondToClick(Click) = 0;
    protected:
        Screen(): Drawable() {};
};


#endif /* SCREEN_H_ */
