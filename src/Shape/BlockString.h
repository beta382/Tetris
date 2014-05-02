/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */

#ifndef BLOCKSTRING_H_
#define BLOCKSTRING_H_

#include "Shape.h"

#include <string>
#include <cctype>

using namespace std;

class BlockString: public Shape {
_registerForLeakcheckWithID(BlockString)
    public:
        
        /*
         * Instantiates a BlockString object using default values.
         */
        BlockString();
        
        /*
         * Instantiates a BlockString object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this BlockString object's x with
         *   int y: The value to initialize this BlockString object's y with
         *   int blockSize: The value to initialize this BlockString object's blockSize with
         *   int padding: The value to initialize this BlockString object's padding with
         *   string str: The value to initialize this BlockString object's string with, defaults to
         *     the empty string
         *   unsigned int background: The value to initialize this BlockString object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this BlockString object's background
         *     with, defaults to Color::BLACK
         */
        BlockString(int x, int y, int blockSize, int padding, string str = "", 
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK);
        
        /*
         * Sets this BlockString object's blocks to represent the passed string.
         * 
         * Parameters:
         *   string str: The string to model this BlockString after
         */
        void setString(string str);
};



#endif /* BLOCKSTRING_H_ */
