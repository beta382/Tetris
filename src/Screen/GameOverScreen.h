/*
 * GameOverScreen.h
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#ifndef GAMEOVERSCREEN_H_
#define GAMEOVERSCREEN_H_

#include "Screen.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "../Shape/BlockString.h"

class MenuScreen;

class GameOverScreen: public Screen {
_registerForLeakcheckWithID(GameOverScreen)
    public:
        GameOverScreen(GameScreen* bgScreen);
        ~GameOverScreen();
        
        void respondToKey(int) throw (QUIT, NEW_SCREEN);
        void respondToClick(Click) throw (QUIT, NEW_SCREEN);
        void doBackground() throw (QUIT, NEW_SCREEN);
        void applyLayout();
        
        void draw();
        void erase();
        
    private:
        
        //Prevent default instantiation, we need a background
        GameOverScreen();
        
        void doMenu() throw (NEW_SCREEN);
        
        GameScreen* bgScreen;
        
        BlockString title;
        BlockString scoreStr;
        BlockString levelStr;
        BlockString scoreNum;
        BlockString levelNum;
        BlockString menu;
};


#endif /* GAMEOVERSCREEN_H_ */
