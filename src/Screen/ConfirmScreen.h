/*
 * ConfirmScreen.h
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#ifndef CONFIRMSCREEN_H_
#define CONFIRMSCREEN_H_

#include "Screen.h"
#include "MenuScreen.h"
#include "../Shape/BlockString.h"

// Forward declaration of destination screens, due to potential for an inclusion loop
class MenuScreen;

class ConfirmScreen: public Screen {
_registerForLeakcheckWithID(ConfirmScreen)
    public:
        ConfirmScreen(Screen* prevScreen);
        ~ConfirmScreen();
        
        void respondToKey(int) throw (QUIT, NEW_SCREEN);
        void respondToClick(Click) throw (QUIT, NEW_SCREEN);
        void doBackground() throw (QUIT, NEW_SCREEN);
        void applyLayout();
        
        void draw();
        void erase();

    private:
        
        //Prevent default instantiation, we need a background
        ConfirmScreen();
        
        void doYes() throw (NEW_SCREEN);
        void doNo() throw (NEW_SCREEN);
        
        Screen* bgScreen;
        BlockString title;
        BlockString yes, no;
};


#endif /* CONFIRMSCREEN_H_ */
