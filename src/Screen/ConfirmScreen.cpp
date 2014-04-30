/*
 * ConfirmScreen.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#include "ConfirmScreen.h"

ConfirmScreen::ConfirmScreen(Screen* prevScreen):
Screen(),
    bgScreen(prevScreen), title(0, 0, 12, 0, "really exit?", Color::LIGHT_GRAY), 
    yes(0, 0, 22, 0, "yes", Color::GREEN), no(0, 0, 22, 0, "no", Color::RED)
{
}

ConfirmScreen::~ConfirmScreen() {
    erase();
    delete bgScreen;
}

void ConfirmScreen::respondToKey(int key) throw (QUIT, NEW_SCREEN) {
    switch(key) {
        case 'y':
        case Key::ENTER:
            CSdoYes();
            break;
        case 'n':
        case Key::BACKSPACE:
            CSdoNo();
            break;
    }
}

void ConfirmScreen::respondToClick(Click click) throw (QUIT, NEW_SCREEN) {
    if (click.button == GLUT_LEFT_BUTTON && click.state == GLUT_UP) {
        if (click.x >= yes.getLocationX() && click.x < yes.getLocationX()+yes.getWidth() &&
            click.y >= yes.getLocationY() && click.y < yes.getLocationY()+yes.getHeight())
        {
            CSdoYes();
        } else if (
            click.x >= no.getLocationX() && click.x < no.getLocationX()+no.getWidth() &&
            click.y >= no.getLocationY() && click.y < no.getLocationY()+no.getHeight())
        {
            CSdoNo();
        }
    }
}

void ConfirmScreen::doBackground() throw (QUIT, NEW_SCREEN) {
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= yes.getLocationX() && cursorX < yes.getLocationX()+yes.getWidth() &&
        cursorY >= yes.getLocationY() && cursorY < yes.getLocationY()+yes.getHeight())
    {
        yes.setForeground(Color::REAL_GREEN);
        no.setForeground(Color::RED);
    } else if (
        cursorX >= no.getLocationX() && cursorX < no.getLocationX()+no.getWidth() &&
        cursorY >= no.getLocationY() && cursorY < no.getLocationY()+no.getHeight())
    {
        no.setForeground(Color::DARK_RED);
        yes.setForeground(Color::GREEN);
    } else {
        yes.setForeground(Color::GREEN);
        no.setForeground(Color::RED);
    }
    
    applyLayout();
    draw();
}

void ConfirmScreen::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());
    
    title.setLocation((getWidth()-title.getWidth())/2, getHeight()-title.getHeight()-30);
    
    yes.setLocation((getWidth()/2-yes.getWidth())/2, (getHeight()-yes.getHeight())/2);
    no.setLocation((3*(getWidth())/2-no.getWidth())/2, (getHeight()-no.getHeight())/2);
}

void ConfirmScreen::draw() {
    if (bgScreen) {
        bgScreen->applyLayout();
        bgScreen->draw();
    }
    
    char* sharedPixelBuffer = g->getBuffer();
    
    // Darkens the screen
    for (int i = 0; i < g->getBufferLen(); i++) {
        sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/4;
    }
    
    title.draw();
    
    yes.draw();
    no.draw();
    
    isVisible = true;
}

void ConfirmScreen::erase() {
    if (isVisible) {
        no.erase();
        yes.erase();
        
        title.erase();
        
        if (bgScreen) {
            bgScreen->erase();
        }
        
        isVisible = false;
    }
}


