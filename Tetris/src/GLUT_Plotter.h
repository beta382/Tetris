/*
 * GLUT_Plotter.h - Header file for plotter class
 *
 * Author: Dr. Booth
 *  Created  on: Mar 19, 2014
 *  Modified on: Mar 22, 2014
 */

#ifndef GLUT_PLOTTER_H_
#define GLUT_PLOTTER_H_

#include <iostream>
#include <cstdlib>
#include <queue>

#include <GLUT/glut.h>

using namespace std;

struct Click {
    int button;
    int state;
    int x;
    int y;
};

class GLUT_Plotter {
    protected:
        int width;
        int height;
        char *buffer;
        queue<int> keyboardQueue;
        queue<Click> mouseQueue;

        unsigned int color;

    public:
        GLUT_Plotter(int width = 500, int height = 500);
        ~GLUT_Plotter() {
            ;
        }

        void Draw(void);
        void Clear();
        void init(int *argc, char **argv);
        void init();

        int getWidth();
        int getHeight();
        char* getBuffer();
        void setColor(unsigned int);
        unsigned int getColor();
        void plot(int x, int y);
        unsigned char getKey();
        bool kbhit() {
            return keyboardQueue.size() > 0;
        }
        void addKeyHit(int key) {
            keyboardQueue.push(key);
        }
        Click getClick();
        bool click() {
            return mouseQueue.size() > 0;
        }
        void addClick(Click c);
        void callBacks();
        void RegisterDisplayFunc(void (*func)(void));
        void RegisterKeyboardFunc(void (*func)(unsigned char key, int x, int y));
        void RegisterSpecialKeyboardFunc(void (*func)(int key, int x, int y));
        void RegisterMouseFunc(void (*func)(int button, int state, int x, int y));
        void RegisterIdleFunc(void (*func)(void));

        void MainLoop();

};

void drawFunction(void);
void keyboardFunction(unsigned char, int, int);
void SpecialKeyboardFunction(int, int, int);
void mouseFunction(int button, int state, int x, int y);

void setpixel(char *buf, int x, int y, int r, int g, int b, int width);

#endif /* GLUT_PLOTTER_H_ */
