#ifndef MENUSCREEN_H_INCLUDED
#define MENUSCREEN_H_INCLUDED

#include "Screen.h"
#include "../Image.h"

class MenuScreen:public Screen
{
    private:
        Image logo;
        Image attribution;
        Image play;
        Image playHover;
        Image howToPlay;
        Image howToPlayHover;
    
    public:
        MenuScreen();
        void draw();
        Screen* doBackground();
        
        
};

#endif // MENUSCREEN_H_INCLUDED
