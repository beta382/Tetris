/*
 * InstructionScreen.h
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#ifndef INSTRUCTIONSCREEN_H_
#define INSTRUCTIONSCREEN_H_

#include "Screen.h"
#include "MenuScreen.h"
#include "../Logo.h"
#include "../BlockString.h"

// Forward declaration of destination screens, due to potential for an inclusion loop
class MenuScreen;

class InstructionScreen: public Screen {
_registerForLeakcheckWithID(InstructionScreen)
    public:
        InstructionScreen(unsigned int color = Color::BLACK);
        
        ~InstructionScreen();
        
        Screen* respondToKey(int) throw (EXIT);
        
        Screen* respondToClick(Click) throw (EXIT);
        
        Screen* doBackground() throw (EXIT);
        
        void applyLayout();
        
        void draw();
        void erase();
    private:
        Logo logo;
        BlockString title;
        BlockString back;
        BlockString keysHeader, scoreHeader;
        BlockString w, s, a, d, q, e, p, esc;
        BlockString p50, p100, px2;
        BlockString attribution;
};

#endif /* INSTRUCTIONSCREEN_H_ */
