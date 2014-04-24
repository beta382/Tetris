/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <ctime>
#include <map>
#include <string>
#include <ostream>
#include <iomanip>

using namespace std;

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

namespace util {
    
    /*
     * Waits the passed number of milliseconds.
     * 
     * Parameters:
     *   clock_t ms: The number of milliseconds to wait
     */
    void wait(clock_t ms);
    
}

struct leakcheck {
    static unsigned int n_new;
    static unsigned int n_delete;
    static map<void*, pair<string, size_t> > allocated;
    
    static ostream& print(ostream& out) {
        for(map<void*, pair<string, size_t> >::const_iterator it = allocated.begin(); it != allocated.end(); it++) {
            out << left << setw(12) << it->first << setw(20) << it->second.first << it->second.second << endl;
        }
        
        return out;
    }
    
    static size_t bytes() {
        size_t sum = 0;
        
        for(map<void*, pair<string, size_t> >::const_iterator it = allocated.begin(); it != allocated.end(); it++) {
            sum += it->second.second;
        }
        
        return sum;
    }
};

// More stuff later, maybe

#endif /* UTIL_H_ */
