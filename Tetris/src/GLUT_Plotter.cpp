/*
 * GLUT_Plotter.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: Dr. Booth
 */

#include "GLUT_Plotter.h"
GLUT_Plotter* g;

GLUT_Plotter::GLUT_Plotter(int w, int h){

	width  = w;
	height = h;
	buffer = new char[width*height*3];
    g = this;
	init();
	callBacks();
	Draw();

}

void GLUT_Plotter::init(){
	int *argc=new int(1);
	char **argv = new char*[1];
	argv[0] = new char[10];
	argv[0][0] = '\0';

	glutInitWindowSize(width, height);

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Tetris");
	//glutFullScreen();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

}

void GLUT_Plotter::init(int *argc, char **argv){

	glutInitWindowSize(width, height);
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Tetris");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    Draw();
}

void GLUT_Plotter::MainLoop(){
	glutMainLoop();
}

void GLUT_Plotter::RegisterKeyboardFunc(void (*func)(unsigned char key, int x, int y)){
	glutKeyboardFunc(func);
}

void GLUT_Plotter::RegisterSpecialKeyboardFunc(void (*func)(int key, int x, int y)){
	glutSpecialFunc(func);
}

void GLUT_Plotter::RegisterDisplayFunc(void (*func)(void)){
	glutDisplayFunc(func);
}


void GLUT_Plotter::RegisterMouseFunc(void (*func)(int button, int state,int x, int y)){
	glutMouseFunc(func);
}

void GLUT_Plotter::RegisterIdleFunc(void (*func)(void)){
	glutIdleFunc(func);
}




void GLUT_Plotter::Clear(){
	memset(buffer,0,width*height*3);
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glutSwapBuffers();
}


void GLUT_Plotter::Draw(void){
	glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer);
	glutSwapBuffers();
	  // instruct event system to call 'drawfunc' again
	//glutPostRedisplay();

}

int GLUT_Plotter::getWidth(){
  return width;
}

int GLUT_Plotter::getHeight(){
  return height;
}


char* GLUT_Plotter::getBuffer(){
	return buffer;
}



void GLUT_Plotter::setColor(unsigned int c){
	color = c;
}

unsigned int GLUT_Plotter::getColor(){
	return color;
}

void GLUT_Plotter::plot(int x, int y){
	unsigned int r,g,b;
	r = (color & 0xff0000)>>16;
	g = (color & 0x00FF00)>>8;
	b = (color & 0x0000FF)>>0;
	setpixel(buffer, x, y, r, g, b, width);
}

void GLUT_Plotter::callBacks(){
	RegisterDisplayFunc(&drawFunction);
	RegisterKeyboardFunc(keyboardFunction);
	RegisterSpecialKeyboardFunc(SpecialKeyboardFunction);
	RegisterMouseFunc(mouseFunction);
}

unsigned char GLUT_Plotter::getKey(){
	int key = -1;
	if(keyboardQueue.size() > 0){
		key = keyboardQueue.front();
		keyboardQueue.pop();
	}

	return key;
}

Click GLUT_Plotter::getClick(){
	Click c;
	c.button = -1;
	c.state = -1;
	c.x = -1;
	c.y = -1;
	if(mouseQueue.size() > 0){
		c = mouseQueue.front();
		mouseQueue.pop();
	}

	return c;
}

void GLUT_Plotter::addClick(Click c){
	mouseQueue.push(c);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void keyboardFunction(unsigned char k, int x, int y) {
    g->addKeyHit(k);
}

void SpecialKeyboardFunction(int k, int x, int y) {
	k+=64;
	keyboardFunction(k,x,y);
}

void mouseFunction(int button, int state,int x, int y){
    Click c;
    c.button = button;
    c.state = state;
    c.x = x;
    c.y = y;
    if(state == 0){
        g->addClick(c);
    }
}

void drawFunction(void){
}

void setpixel(char *buf, int x, int y, int r, int g, int b, int width) {
   buf[(y*width+x)*3+0] = r;
   buf[(y*width+x)*3+1] = g;
   buf[(y*width+x)*3+2] = b;
}
