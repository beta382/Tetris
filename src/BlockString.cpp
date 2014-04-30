/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */

#include "BlockString.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a BlockString object using default values.
 */
BlockString::BlockString():
Shape()
{
}

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
 *   unsigned int background: The value to initialize this BlockString object's background
 *     with, defaults to Color::BLACK
 */
BlockString::BlockString(int x, int y, int blockSize, int padding, string str,
        unsigned int foreground, unsigned int background):
Shape(x, y, blockSize, padding, background)
{
    this->foreground = foreground;
    setString(str);
}


/* ---------- Public ---------- */

/*
 * Sets this BlockString object's blocks to represent the passed string.
 * 
 * Parameters:
 *   string str: The string to model this BlockString after
 */
void BlockString::setString(string str) {
    
    for (unsigned int i = 0; i < blocks.size(); i++) {
        delete blocks[i];
        blocks[i] = NULL;
    }
    
    blocks.clear();
    
    for (unsigned int i = 0; i < str.length(); i++) {
        switch (toupper(str.at(i))) {
            case 'A':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'B':
            case '8':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'C':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 4);
                break;
            case 'D':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3);
                break;
            case 'E':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'F':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 4);
                break;
            case 'G':
            case '6':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 4);
                break;
            case 'H':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2)
                    .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'I':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 1).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 3)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 4);
                break;
            case 'J':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 4)
                    .addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'K':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'L':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+2, 0);
                break;
            case 'M':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 3).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'N':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 1)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 3).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'O':
            case '0':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'P':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'Q':
                addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2).addBlock<Block>(i*4, 3)
                    .addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 1)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'R':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'S':
            case '5':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 2).addBlock<Block>(i*4, 3)
                    .addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 4);
                break;
            case 'T':
                addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 1)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 3).addBlock<Block>(i*4+1, 4)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case 'U':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2)
                    .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'V':
                addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 1)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'W':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 1)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'X':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 3)
                    .addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'Y':
                addBlock<Block>(i*4, 2).addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4)
                    .addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 1).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case 'Z':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 4)
                    .addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4)
                    .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case '1':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 1).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 3)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0);
                break;
            case '2':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 2)
                    .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case '3':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case '4':
                addBlock<Block>(i*4, 2).addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case '7':
                addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4)
                .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2)
                .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case '9':
                addBlock<Block>(i*4, 2).addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4)
                    .addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0)
                    .addBlock<Block>(i*4+2, 1).addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3)
                    .addBlock<Block>(i*4+2, 4);
                break;
            case ':':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 3)
                .addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 1)
                .addBlock<Block>(i*4+1, 3).addBlock<Block>(i*4+1, 4);
                break;
            case ',':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4+1, -1)
                .addBlock<Block>(i*4+1, 0).addBlock<Block>(i*4+1, 1);
                break;
            case '-':
                addBlock<Block>(i*4, 2).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+2, 2);
                break;
            case '<':
                addBlock<Block>(i*4, 2).addBlock<Block>(i*4+1, 1).addBlock<Block>(i*4+1, 3)
                    .addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 4);
                break;
            case '/':
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4+1, 2)
                    .addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
            case ' ':
                break;
            default:
                addBlock<Block>(i*4, 0).addBlock<Block>(i*4, 1).addBlock<Block>(i*4, 2)
                    .addBlock<Block>(i*4, 3).addBlock<Block>(i*4, 4).addBlock<Block>(i*4+1, 0)
                    .addBlock<Block>(i*4+1, 1).addBlock<Block>(i*4+1, 2).addBlock<Block>(i*4+1, 3)
                    .addBlock<Block>(i*4+1, 4).addBlock<Block>(i*4+2, 0).addBlock<Block>(i*4+2, 1)
                    .addBlock<Block>(i*4+2, 2).addBlock<Block>(i*4+2, 3).addBlock<Block>(i*4+2, 4);
                break;
        }
    }
}
