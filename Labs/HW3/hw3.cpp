#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"
#include "Room.h"
#include "lib.h"
#include <iostream>

#define PI 3.141592653589793

Room room;

bool showCoords = false;

// global values for camera
GLdouble eyex = 25.0, eyey = 5.0, eyez = 25.0;
GLdouble lookx = 0.0, looky = 0.0, lookz = 0.0;

// global values for shading
GLfloat ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 50.0f };

GLfloat position[] = { 10.0f, 6.0f, 15.0f, 0.0f };
GLfloat lightIntensity[] = { 0.7f, 0.7f, 0.7f, 1.0f };

void myInit();
void myIdle();
void myDisplay();
void myKeyboard(unsigned char, int, int);
void mySpecialKeys(int, int, int);
void myMouse(int, int);

int main(int argc, char **argv) {
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Homework 2"); // open the screen window

	myInit();

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
	glutMotionFunc(myMouse);
	glutPassiveMotionFunc(myMouse);
	//glutMouseFunc

	glutMainLoop();

	return(0);
}

void myInit() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glDisable(GL_COLOR_MATERIAL);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	room.getCamera()->setShape(50.0f, 64.0f / 48.0f, 0.5f, 1000.0f);
	room.updateCamera();
}

void myIdle() {
	room.animate();
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void myDisplay() {
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen

	glPushMatrix();
		room.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'A':
		room.shiftRobotLeft();
	case 'a':
		room.shiftRobotLeft();
		break;
	case 'D':
		room.shiftRobotRight();
	case 'd':
		room.shiftRobotRight();
		break;
	case 'q':
	case 'Q':
		room.getRobot()->doAttack(1);
		break;
	case 'w':
	case 'W':
		room.getRobot()->doAttack(2);
		break;
	case 'e':
	case 'E':
		room.getRobot()->doAttack(3);
	}
	glutPostRedisplay();
}

void mySpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_PAGE_UP:
		// slide camera forward
		std::cout << "Camera zoom-in" << std::endl;
		room.getCamera()->slide(0, 0, -0.2);
		break;
	case GLUT_KEY_PAGE_DOWN:
		// slide camera backward
		std::cout << "Camera zoom-out" << std::endl;
		room.getCamera()->slide(0, 0, 0.2);
		break;
	}
	glutPostRedisplay();
}

void myMouse(int x, int y) {
	if (x < 0) {
		x = 0;
	} else if (x > screenWidth) {
		x = screenWidth;
	}

	GLdouble _x = static_cast<GLdouble>(screenWidth) / 2.0 - static_cast<GLdouble>(x);

	if (y < 0) {
		y = 0;
	} else if (y > screenHeight) {
		y = screenHeight;
	}

	GLdouble _y = static_cast<GLdouble>(screenHeight) / 2.0 - static_cast<GLdouble>(y);

	room.updateCamera((_x / static_cast<GLdouble>(screenWidth) * 2.0), (_y / static_cast<GLdouble>(screenHeight) / 2.0));
	
}