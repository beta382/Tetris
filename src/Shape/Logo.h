/*
 * Logo.h
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#ifndef LOGO_H_
#define LOGO_H_

#include "Shape.h"

class Logo: public Shape {
_registerForLeakcheckWithID(Logo)
    public:
        Logo();
        Logo(int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);
        
    private:
        void init();
};


#endif /* LOGO_H_ */
