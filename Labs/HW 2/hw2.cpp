#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include "gl/glut.h"
#include "Robot.h"
#include <iostream>

#define PI 3.141592653589793

Robot robot;

const int screenWidth = 500, screenHeight = 500;
const float worldWidth = 500.0, worldHeight = 500.0, degreeSegement = 40.0;

bool showCoords = false;

// global values for camera
GLdouble eyex = 25.0, eyey = 17.5, eyez = 25.0;
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
void displaySystem();
void myKeyboard(unsigned char, int, int);
void mySpecialKeys(int, int, int);

int main(int argc, char **argv) {
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Homework 2"); // open the screen window

	myInit();

	glutDisplayFunc(displaySystem);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);

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
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	//glOrtho(-3.5*worldWidth / worldHeight, 3.5*worldWidth / worldHeight, -3.5, 3.5, 100, 100000);
	glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 110);
}

void myIdle() {
	robot.animate();
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySystem() {
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

	//Draw Axis
	if (showCoords) {
		//Draw Axis
		glBegin(GL_LINES);
		//x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		//y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 100, 0);
		//z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 100);
		glEnd();
	}	

	glPushMatrix();
		//glScaled(0.1, 0.1, 0.1);
		glColor3d(0.4, 0.4, 0.4);
		robot.draw();
	glPopMatrix();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'i':
			robot.setShoulderAngle(-360.0 / degreeSegement);
			break;
		case 'I':
			robot.setShoulderAngle(360.0 / degreeSegement);
			break;
		case 'j':
			robot.setArmAngle(-360.0 / degreeSegement);
			break;
		case 'J':
			robot.setArmAngle(360.0 / degreeSegement);
			break;
		case 'n':
			robot.setHandAngle(-360.0 / degreeSegement);
			break;
		case 'N':
			robot.setHandAngle(360.0 / degreeSegement);
			break;
		case 'm':
			robot.setFingerAngle(-360.0 / degreeSegement);
			break;
		case 'M':
			robot.setFingerAngle(360.0 / degreeSegement);
			break;
		case 'r':
			robot.setRotate(-360.0 / degreeSegement);
			break;
		case 'R':
			robot.setRotate(360.0 / degreeSegement);
			break;
		case 'o':
		case 'O':
			robot.toggleActivation();
			break;
		case 'u':
		case 'U':
			robot.toggleWireframe();
			break;
		case 'c':
		case 'C':
			showCoords = !showCoords;
			break;
		case 27:
			robot.reset();
			break;
		case 'q':
		case 'Q':
			robot.stopAnimation();
			exit(0);
			break;
		case 'a':
		case 'A':
			robot.toggleAnimation();
			break;
	}
	glutPostRedisplay();
}

void mySpecialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			robot.setX(2);
			break;
		case GLUT_KEY_DOWN:
			robot.setX(-2);
			break;
	}
	glutPostRedisplay();
}