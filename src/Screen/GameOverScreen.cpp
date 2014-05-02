/*
 * GameOverScreen.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */

#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(GameScreen* bgScreen):
Screen(),
        bgScreen(bgScreen), title(0, 0, 16, 0, "game over!", Color::RED),
        scoreStr(0, 0, 12, 0, "Score:", Color::GREEN),
        levelStr(0, 0, 12, 0, "Level:", Color::GREEN),
        scoreNum(0, 0, 12, 0, util::itoa(bgScreen->getScore()), Color::GRAY),
        levelNum(0, 0, 12, 0, util::itoa(bgScreen->getLevel()), Color::GRAY),
        menu(0, 0, 10, 0, "return to menu", Color::LIGHT_GRAY)
{
    id = 6;
}

GameOverScreen::~GameOverScreen() {
    erase();
    delete bgScreen;
}

void GameOverScreen::respondToKey(int key) throw (QUIT, NEW_SCREEN) {
    switch (key) {
        case Key::ESC:
        case Key::ENTER:
            doMenu();
            break;
    }
}

void GameOverScreen::respondToClick(Click click) throw (QUIT, NEW_SCREEN) {
    if (click.button == GLUT_LEFT_BUTTON && click.state == GLUT_UP) {
        if (click.x >= menu.getLocationX() && click.x < menu.getLocationX()+menu.getWidth() &&
            click.y >= menu.getLocationY() && click.y < menu.getLocationY()+menu.getHeight())
        {
            doMenu();
        }
    }
}

void GameOverScreen::doBackground() throw (QUIT, NEW_SCREEN) {
    int cursorX = g->getMouseX();
    int cursorY = g->getMouseY();
    
    if (cursorX >= menu.getLocationX() && cursorX < menu.getLocationX()+menu.getWidth() &&
        cursorY >= menu.getLocationY() && cursorY < menu.getLocationY()+menu.getHeight())
    {
        menu.setForeground(Color::GRAY);
    } else {
        menu.setForeground(Color::LIGHT_GRAY);
    }
    
    applyLayout();
    draw();
}

void GameOverScreen::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());
    
    title.setLocation((getWidth()-title.getWidth())/2, getHeight()-title.getHeight()-30);
    
    scoreStr.setLocation(getWidth()/3-scoreStr.getWidth()/2, getHeight()/2+50);
    levelStr.setLocation(scoreStr.getLocationX()+scoreStr.getWidth()-levelStr.getWidth(), 
            scoreStr.getLocationY()-levelStr.getHeight()-scoreStr.getTotalBlockSize()*4);
    
    scoreNum.setLocation(scoreStr.getLocationX()+scoreStr.getWidth()+scoreStr.getTotalBlockSize()
            *3, scoreStr.getLocationY()+(scoreStr.getHeight()-scoreNum.getHeight())/2);
    levelNum.setLocation(levelStr.getLocationX()+levelStr.getWidth()+levelStr.getTotalBlockSize()
            *3, levelStr.getLocationY()+(levelStr.getHeight()-levelNum.getHeight())/2);
    
    menu.setLocation((getWidth()-menu.getWidth())/2, 30);
}

void GameOverScreen::draw() {
    if (bgScreen) {
        bgScreen->applyLayout();
        bgScreen->draw();
    }
    
    char* sharedPixelBuffer = g->getBuffer();
    
    // Darkens the screen
    for (int i = 0; i < g->getBufferLen(); i++) {
        sharedPixelBuffer[i] = static_cast<unsigned char>(sharedPixelBuffer[i])/8;
    }
    
    title.draw();
    menu.draw();
    scoreStr.draw();
    levelStr.draw();
    scoreNum.draw();
    levelNum.draw();
    
    isVisible = true;
}

void GameOverScreen::erase() {
    if (isVisible) {
        levelNum.erase();
        scoreNum.erase();
        levelStr.erase();
        scoreStr.erase();
        menu.erase();
        title.erase();
        
        isVisible = false;
    }
}

void GameOverScreen::doMenu() throw (NEW_SCREEN) {
    throw NEW_SCREEN(new MenuScreen(Color::TAN));
}
