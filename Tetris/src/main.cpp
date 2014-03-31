/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 27, 2014
 * Date last modified:     Mar 27, 2014
 */

#include <iostream>
#include "PlayingField.h"
#include "Tetromino.h"

#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    
    PlayingField field(3, 3, 10, 20);
    Tetromino *currentTetromino = field.spawnNewTetromino(3, 0, S);
    
    srand(time(0));
    
    char curChar;
    
    int prevX;
    int prevY;
    
    currentTetromino->draw();
    
    do {
        switch (curChar) {
            case 'w':
                if (field.canShiftUp(currentTetromino)) {
                    currentTetromino->shiftUp();
                }
                break;
            case 'a':
                if (field.canShiftLeft(currentTetromino)) {
                    currentTetromino->shiftLeft();
                }
                break;
            case 's':
                if (field.canShiftDown(currentTetromino)) {
                    currentTetromino->shiftDown();
                }
                break;
            case 'd':
                if (field.canShiftRight(currentTetromino)) {
                    currentTetromino->shiftRight();
                }
                break;
            case 'c':
                currentTetromino->setColor(static_cast<ink>(rand() % 16));
                currentTetromino->draw();
                break;
            case 'q':
                if (field.canRotateCCW(currentTetromino)) {
                    currentTetromino->rotateCCW();
                }
                break;
            case 'e':
                if (field.canRotateCW(currentTetromino)) {
                    currentTetromino->rotateCW();
                }
                break;
            case 'n':
                prevX = currentTetromino->getLocationX();
                prevY = currentTetromino->getLocationY();
                
                delete currentTetromino;
                currentTetromino = field.spawnNewTetromino(prevX-field.getLocationX(), prevY-field.getLocationY(), 
                        static_cast<TetrominoShape>(rand() % 7));
                currentTetromino->draw();
                break;
            case 'j':
                field.merge(currentTetromino);
                
                currentTetromino = field.spawnNewTetromino(3, 3, static_cast<TetrominoShape>(rand() % 7));
                currentTetromino->draw();
                break;
            case 'm':
                field.setLocation(0,0);
                break;
        }
        
        field.draw();
    } while ((curChar = getch()) != 'x');
    
    delete currentTetromino;
    
    return 0;
}












