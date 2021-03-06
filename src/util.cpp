/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 15, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "util.h"

/*
 * Waits the passed number of milliseconds.
 * 
 * Parameters:
 *   unsigned int ms: The number of milliseconds to wait
 *   GLUT_Plotter* g: A pointer to a GLUT_Plotter object we should prevent from registering events
 */
void util::wait(clock_t ms, GLUT_Plotter* g) {
    clock_t end = clock()+ms;
    
    g->Draw(); // Force redraw before we wait
    
    while (clock() < end);
    
    g->callBacks(false);
    glutMainLoopEvent();
    g->callBacks(true);
}

/*
 * An itoa function that doesn't suck to use
 */
string util::itoa(int i) {
    string str;
    
    do {
        str.insert(0, 1, static_cast<char>(i%10+48));
        i /= 10;
    } while (i > 0);
    
    return str;
}


map<void*, pair<string, size_t> > leakcheck::allocated;

#ifdef DO_LEAKCHECK

    /*
     * Reports data on all objects on the heap being tracked by leakcheck, as well as a concise
     *   summary of the number of tracked objects on the heap and the number of bytes they are
     *   collectively using.
     * 
     * Parameters:
     *   ostream& out: The output stream to send the report
     */
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
    
    /*
     * Returns the collective number of bytes of all objects on the heap being tracked by leakcheck
     */
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
    
