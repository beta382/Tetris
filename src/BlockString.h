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
    public:
        BlockString();
        
        BlockString(int x, int y, int blockSize, int padding, string str = "",
                unsigned int background = Color::BLACK);
        
        void setString(string str);
};



#endif /* BLOCKSTRING_H_ */
