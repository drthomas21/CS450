#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"

#include <iostream>
#include <cmath>
#include <fstream>

const int screenWidth = 600;
const int screenHeight = 600;
const float worldWidth = 500.0;
const float worldHeight = 500.0;

void setWindow(float, float, float, float);

void myInit();
void myIdle();
void myDisplay();

void drawGround();

int main(int argc, char** argv) {
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw callback function
	glutIdleFunc(myIdle);			// register idle callback function

	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
}

void setWindow(float left, float right, float bottom, float top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);      // background color is white
	glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue
	setWindow(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2); // replaces the following three lines
}

void drawGround() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-worldWidth / 2, -worldHeight / 2);
	glVertex2d(worldWidth / 2, -worldHeight / 2);
	glVertex2d(-worldWidth / 2, -worldHeight / 2 + 20.0);
	glVertex2d(worldWidth / 2, -worldHeight / 2 + 20.0);
	glEnd();
}