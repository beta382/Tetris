/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 26, 2014
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "GLUT_Plotter.h"

#include <ctime>

#include <cstdlib>
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
    const unsigned int DARK_GREEN = 0x69803e;
    const unsigned int REAL_GREEN = 0x0b610b;
    const unsigned int GRAY       = 0x52656b;
    const unsigned int LIGHT_GRAY = 0x92abb0;
    const unsigned int RED        = 0xb04747;
    const unsigned int DARK_RED   = 0xb40404;
    const unsigned int TAN        = 0xe3decd;
    const unsigned int LIGHT_TAN  = 0xfff9e6;
    const unsigned int DARK_TAN   = 0xcdc7b9;
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
     *   GLUT_Plotter* g: A pointer to a GLUT_Plotter object we should prevent from registering
     *     events
     */
    void wait(clock_t ms, GLUT_Plotter* g);
}

#ifdef DO_LEAKCHECK

    /*
     * This is a macro for leakcheck which you are supposed to add somewhere in your object
     *   declaration if you want dynamically allocated instances of that object to be tracked.
     *  
     * Overrides 'operator new' and 'operator delete' for the class in question with an
     *   implementation that logs dynamic allocations of tracked objects to a map structure, which
     *   can be displayed at any time by calling leakcheck::report().
     *   
     * id should be the string representation of the name of the object you are tracking, WITHOUT
     *   string-literal double quotes.
     */

#    define _registerForLeakcheckWithID(id) \
        public: \
        void* operator new(size_t bytes) { \
            void* mem = malloc(bytes); \
            leakcheck::allocated.insert(std::pair<void*, std::pair<std::string, size_t> > \
                    (mem, std::pair<std::string, size_t>(#id, bytes))); \
            return mem; \
        } \
        void operator delete(void* mem) { \
            leakcheck::allocated.erase(mem); \
            free(mem); \
        }
    /* end define */

#else // Define empty macro if we aren't checking for leaks
#    define _registerForLeakcheckWithID(id)
#endif

namespace leakcheck {
    
    /*
     * Holds the address, identifier, and number of bytes of each currently allocated object
     *   being tracked by leakcheck on the heap.
     */
    extern map<void*, pair<string, size_t> > allocated;
    
    /*
     * Reports data on all objects on the heap being tracked by leakcheck, as well as a concise
     *   summary of the number of tracked objects on the heap and the number of bytes they are
     *   collectively using.
     * 
     * Parameters:
     *   ostream& out: The output stream to send the report
     */
    void report(ostream& out);
    
    /*
     * Returns the collective number of bytes of all objects on the heap being tracked by leakcheck
     */
    size_t bytes();
}

// More stuff later, maybe

#endif /* UTIL_H_ */
