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

#ifdef DO_LEAKCHECK
    #include <cstdlib>
    #include <map>
    #include <string>
    #include <ostream>
    #include <iomanip>
#endif

/* ---------- Color codes ---------- */

namespace Color {
    
    const unsigned int WHITE      = 0xFFFFFF;
    const unsigned int BLACK      = 0x000000;
    const unsigned int BLUE       = 0x358fa1;
    const unsigned int BROWN      = 0xab9c6d;
    const unsigned int GREEN      = 0xa6c238;
    const unsigned int GRAY       = 0x52656b;
    const unsigned int LIGHT_GRAY = 0x92abb0;
    const unsigned int RED        = 0xb04747;
    const unsigned int TAN        = 0xe3decd;
    const unsigned int LIGHT_TAN  = 0xfff9e6;
    const unsigned int DARK_TAN   = 0xcdc7b9;
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

#ifdef DO_LEAKCHECK

    #define _registerForLeakcheckWithID(id) \
        public: \
        void* operator new(size_t bytes) { \
            void* mem = malloc(bytes); \
            leakcheck::n_new++; \
            leakcheck::allocated.insert(std::pair<void*, std::pair<std::string, size_t> > \
                    (mem, std::pair<std::string, size_t>(#id, bytes))); \
            return mem; \
        } \
        void operator delete(void* mem) { \
            leakcheck::n_delete++; \
            leakcheck::allocated.erase(mem); \
            free(mem); \
        }

    using namespace std;
    
    namespace leakcheck {
        extern unsigned int n_new;
        extern unsigned int n_delete;
        extern map<void*, pair<string, size_t> > allocated;
        
        void report(ostream& out);
        size_t bytes();
    }
#endif

// More stuff later, maybe

#endif /* UTIL_H_ */
