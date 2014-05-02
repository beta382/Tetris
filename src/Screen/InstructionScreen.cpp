/*
 * InstructionScreen.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#include "InstructionScreen.h"

InstructionScreen::InstructionScreen(unsigned int color):
Screen(color),
        logo(0, 0, 5, 1, background), 
        title(0, 0, 8, 0, "how to play", Color::BLACK, background),
        back(0, 0, 4, 0, "<back", Color::GRAY, background),
        keysHeader(0, 0, 5, 0, "keys:", Color::BLACK, background),
        scoreHeader(0, 0, 5, 0, "scoring", Color::BLACK, background),
        w(0, 0, 4, 0, "- w/up: instantly drops", Color::GRAY, background),
        s(0, 0, 4, 0, "- s/down: accelerates fall", Color::GRAY, background),
        a(0, 0, 4, 0, "- a/left: move left", Color::GRAY, background),
        d(0, 0, 4, 0, "- d/right: move right", Color::GRAY, background),
        q(0, 0, 4, 0, "- q: rotate counter-clockwise", Color::GRAY, background),
        e(0, 0, 4, 0, "- e: rotate clockwise", Color::GRAY, background),
        p(0, 0, 4, 0, "- p/space: pauses and un-pauses game", Color::GRAY, background),
        esc(0, 0, 4, 0, "- esc: exits game", Color::GRAY, background),
        p50(0, 0, 4, 0, "- 50: clear a line", Color::GRAY, background),
        p100(0, 0, 4, 0, "- 100: clear a special block", Color::GRAY, background),
        px2(0, 0, 4, 0, "- double for a cascading line clear", Color::GRAY, background),
        attribution(0, 0, 2, 0, 
                "created by: wes cossick, evan green, austin hash, and taylor jones", Color::GRAY,
                background)
{
}

InstructionScreen::~InstructionScreen() {
    erase();
}



void InstructionScreen::respondToKey(int key) throw (QUIT, NEW_SCREEN) {
    switch (key) {
        case 'b':
        case Key::BACKSPACE:
            doMenu();
    }
}

void InstructionScreen::respondToClick(Click click) throw (QUIT, NEW_SCREEN) {
    if (click.button == GLUT_LEFT_BUTTON && click.state == GLUT_UP) {
        if (click.x >= back.getLocationX() && 
                click.x < back.getLocationX()+back.getWidth() &&
            click.y >= back.getLocationY() && 
                click.y < back.getLocationY()+back.getHeight())
        {
            doMenu();
        }
    }
}

void InstructionScreen::doBackground() throw (QUIT, NEW_SCREEN) {
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= back.getLocationX() && 
            cursorX < back.getLocationX()+back.getWidth() &&
        cursorY >= back.getLocationY() && 
            cursorY < back.getLocationY()+back.getHeight())
    {
        back.setForeground(Color::BLACK);
    } else {
        back.setForeground(Color::GRAY);
    }
    
    applyLayout();
    draw();
}

void InstructionScreen::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());

    bgRect.setWidth(getWidth());
    bgRect.setHeight(getHeight());
    
    title.setLocation((getWidth()-title.getWidth())/2, getHeight()-title.getHeight()-10);
    
    back.setLocation(20, title.getLocationY()+(title.getHeight()-back.getHeight())/2);
    
    logo.setLocation(getWidth()-logo.getWidth()-back.getLocationX(), 
            title.getLocationY()+(title.getHeight()-logo.getHeight())/2);
    
    keysHeader.setLocation(30, title.getLocationY()-keysHeader.getHeight()-30);
    w.setLocation(keysHeader.getLocationX()+20, keysHeader.getLocationY()-w.getHeight()-20);
    s.setLocation(w.getLocationX(), w.getLocationY()-s.getHeight()-12);
    a.setLocation(w.getLocationX(), s.getLocationY()-a.getHeight()-12);
    d.setLocation(w.getLocationX(), a.getLocationY()-d.getHeight()-12);
    q.setLocation(w.getLocationX(), d.getLocationY()-q.getHeight()-12);
    e.setLocation(w.getLocationX(), q.getLocationY()-e.getHeight()-12);
    p.setLocation(w.getLocationX(), e.getLocationY()-p.getHeight()-12);
    esc.setLocation(w.getLocationX(), p.getLocationY()-esc.getHeight()-12);
    
    scoreHeader.setLocation(keysHeader.getLocationX(),
            esc.getLocationY()-scoreHeader.getHeight()-30);
    p50.setLocation(scoreHeader.getLocationX()+20, scoreHeader.getLocationY()-p50.getHeight()-20);
    p100.setLocation(p50.getLocationX(), p50.getLocationY()-p100.getHeight()-12);
    px2.setLocation(p100.getLocationX(), p100.getLocationY()-px2.getHeight()-12);
    
    attribution.setLocation((getWidth()-attribution.getWidth())/2, 10);
}


void InstructionScreen::draw() {
    bgRect.draw();
    logo.draw();
    title.draw();
    back.draw();
    keysHeader.draw();
    scoreHeader.draw();
    w.draw();
    s.draw();
    a.draw();
    d.draw();
    q.draw();
    e.draw();
    p.draw();
    esc.draw();
    p50.draw();
    p100.draw();
    px2.draw();
    attribution.draw();
    isVisible = true;
}


void InstructionScreen::erase() {
    if (isVisible) {
        logo.erase();
        title.erase();
        back.erase();
        keysHeader.erase();
        scoreHeader.erase();
        w.erase();
        s.erase();
        a.erase();
        d.erase();
        q.erase();
        e.erase();
        p.erase();
        esc.erase();
        p50.erase();
        p100.erase();
        px2.erase();
        attribution.erase();
        bgRect.erase();
        
        isVisible = false;
    }
}

void InstructionScreen::doMenu() throw (NEW_SCREEN) {
    throw NEW_SCREEN(new MenuScreen(Color::TAN));
}
