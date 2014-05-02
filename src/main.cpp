//============================================================================
// Name        : Tetris Driver.cpp
// Author      : Dr. Booth
// Version     :
// Copyright   : Your copyright notice
// Description : Main Driver For Group Project
//============================================================================

#include <iostream>
#include "Drawable.h"
#include "Tetris.h"
#include "util.h"
using namespace std;

void Player(void);
Tetris* game;

int main() {
    GLUT_Plotter* g = new GLUT_Plotter(700, 600); //Create plotter 
    Drawable::setG(g);                    //Give all drawable objects the same static GLUT_Plotter
    game = new Tetris(g);                 //Create Game (Tetris)
    g->RegisterIdleFunc(Player);          //Register Callback 
    g->MainLoop();                        //Enter main loop
    return 0;
}

void Player(void){
    game->Play();
}
