/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 10, 2014
 * Date last modified:     Apr 11, 2014
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "Drawable.h"
#include "Rectangle.h"

class Screen: public Drawable {
    public:
        
        /*
         * Performs an action based on the passed key
         */
        virtual Screen *respondToKey(int) = 0;
        
        /*
         * Performs an action based on the passed Click
         */
        virtual Screen *respondToClick(Click) = 0;
        
        /*
         * Performs actions that should happen continuously in the background on this Screen
         */
        virtual void doBackground() = 0;
    protected:
        
        /*
         * Instantiates a Screen object using the passed foreground color
         * 
         * color defaults to Color::BLACK if nothing is passed
         * 
         * Calls Drawable(0, 0, g->getWidth, g->getHeight(), color) 
         * Initializes bgRect with MyRectangle(0, 0, width, height, color)
         */
        Screen(unsigned int color = Color::BLACK):
            Drawable(0, 0, g->getWidth(), g->getHeight(), color), 
            bgRect(0, 0, width, height, color) {};
        
        MyRectangle bgRect;
};


#endif /* SCREEN_H_ */
