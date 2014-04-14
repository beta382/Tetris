/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr  8, 2014
 */

#ifndef UTIL_H_
#define UTIL_H_

/* ---------- Color codes ---------- */

namespace Color {
    
    const unsigned int WHITE      = 0xFFFFFF;
    const unsigned int BLACK      = 0x000000;
    const unsigned int BLUE       = 0x358fa1;
    const unsigned int BROWN      = 0xab9c6d;
    const unsigned int GREEN      = 0xa6c238;
    const unsigned int GRAY       = 0x52656b;
    const unsigned int RED        = 0xb04747;
    const unsigned int TAN        = 0xe3decd;
    const unsigned int DARK_GREEN = 0x69803e;
    const unsigned int CYAN       = 0x3cad91;
    
}

/* ---------- Key codes ---------- */

namespace Key {
    
    const int UP = 165;
    const int DOWN = 167;
    const int LEFT = 164;
    const int RIGHT = 166;
    const int ESC = 27;
    
}

// More stuff later, maybe

#endif /* UTIL_H_ */