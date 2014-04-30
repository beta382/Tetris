/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 29, 2014
 * Date last modified:     Apr 29, 2014
 */

#include "BlockString.h"

BlockString::BlockString():
Shape()
{
}

BlockString::BlockString(int x, int y, int blockSize, int padding, string str,
        unsigned int background):
Shape(x, y, blockSize, padding, background)
{
    setString(str);
}

void BlockString::setString(string str) {
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
