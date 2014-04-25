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

map<void*, pair<string, size_t> > leakcheck::allocated;

#ifdef DO_LEAKCHECK
    void leakcheck::report(ostream& out) {
        out << setfill('-') << setw(79) << "" << endl;
        out << setfill(' ') << endl;
        
        if (allocated.size() > 0) {
            out << "Tracked objects on heap:" << endl;
            for(map<void*, pair<string, size_t> >::const_iterator it = allocated.begin();
                    it != allocated.end(); it++)
            {
                out << left << setw(12) << it->first << setw(20) << it->second.first <<
                        it->second.second << endl;
            }
        } else {
            out << "No tracked objects on heap." << endl;
        }
        
        out << endl;
        out << "Currently have " << allocated.size() << " objects allocated consuming " << 
                bytes() << " bytes." << endl;
        out << endl;
        out << setfill('-') << setw(79) << "" << endl;
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
#else // Define empty functions if we aren't checking for leaks
    void leakcheck::report(ostream& out) {}
    size_t leakcheck::bytes() {return 0;}
#endif
    
