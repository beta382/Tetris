/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 15, 2014
 * Date last modified:     Apr 15, 2014
 */

#include "util.h"

/*
 * Waits the passed number of milliseconds.
 * 
 * Parameters:
 *   unsigned int ms: The number of milliseconds to wait
 */
void util::wait(clock_t ms) {
    clock_t start = clock();
    
    while (clock() < start+ms);
}

#ifdef DO_LEAKCHECK
    unsigned int leakcheck::n_new = 0;
    unsigned int leakcheck::n_delete = 0;
    map<void*, pair<string, size_t> > leakcheck::allocated;
    
    ostream& leakcheck::print(ostream& out) {
        for(map<void*, pair<string, size_t> >::const_iterator it = allocated.begin();
                it != allocated.end(); it++)
        {
            out << left << setw(12) << it->first << setw(20) << it->second.first <<
                    it->second.second << endl;
        }
        
        return out;
    }
    
    size_t leakcheck::bytes() {
        size_t sum = 0;
        
        for(map<void*, pair<string, size_t> >::const_iterator it = allocated.begin(); 
                it != allocated.end(); it++)
        {
            sum += it->second.second;
        }
        
        return sum;
    }
    
#endif
