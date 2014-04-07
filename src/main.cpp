//============================================================================
// Name        : Tetris Driver.cpp
// Author      : Dr. Booth
// Version     :
// Copyright   : Your copyright notice
// Description : Main Driver For Group Project
//============================================================================

#include <iostream>
#include "Tetris.h"
using namespace std;

void Player(void);
Tetris *game;

int main() {
    GLUT_Plotter *g = new GLUT_Plotter(); //Create plotter 
    game = new Tetris(g);                 //Create Game (Tetris)
    g->RegisterIdleFunc(Player);          //Register Callback 
    g->MainLoop();                        //Enter main loop
    return 0;
}

void Player(void){
    game->Play();
}
