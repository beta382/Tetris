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

unsigned int leakcheck::n_new = 0;
unsigned int leakcheck::n_delete = 0;
