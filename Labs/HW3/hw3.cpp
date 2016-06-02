#ifndef LIB_H
#include "lib.h"
#endif
#include "Room.h"
#include <iostream>

#define PI 3.141592653589793

Room room;

bool capture = false;
GLdouble cameraOffsetX = 0, cameraOffsetY = 0, prevCameraX = 0, prevCameraY = 0;

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
void myMouse(int, int, int, int);
void myMousePassive(int, int);

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
	glutMouseFunc([](int button, int state, int x, int y) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			capture = state == 0;
			if (capture) {
				prevCameraX = screenWidth / 2.0;
				prevCameraY = screenHeight / 2.0;
				glutWarpPointer(screenWidth / 2.0, screenHeight / 2.0);
			}
			break;
		}
	});
	glutMotionFunc([](int x, int y) {		
		if (capture && x >= 0 && x <= screenWidth && y >= 0 && y <= screenHeight) {
			cameraOffsetX += x - prevCameraX;
			cameraOffsetY += y - prevCameraY;
			prevCameraX = x;
			prevCameraY = y;

			if (cameraOffsetY < 0.25) cameraOffsetY = 0.25;
			if (cameraOffsetY > 150) cameraOffsetY = 150;
			room.updateCamera(cameraOffsetX, cameraOffsetY);
		}
	});
	//glutMouseFunc

	glutMainLoop();

	return(0);
}

void myInit() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_DEPTH_TEST);

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
	glEnable(GL_DEPTH_TEST);

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
		room.getRobot()->doAttack(1,room.getTime());
		break;
	case 'w':
	case 'W':
		room.getRobot()->doAttack(2,room.getTime());
		break;
	case 'e':
	case 'E':
		room.getRobot()->doAttack(3,room.getTime());
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

void myMouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			capture = state == 1;
			break;
	}
}


void myMousePassive(int x, int y) {
	if (!capture) return;
	if (x < 0) {
		glutWarpPointer(0, y);
	} else if (x > screenWidth) {
		glutWarpPointer(screenWidth, y);
	}

	GLdouble _x = static_cast<GLdouble>(screenWidth) / 2.0 - static_cast<GLdouble>(x);

	if (y < 0) {
		glutWarpPointer(x, 0);
	} else if (y > screenHeight) {
		glutWarpPointer(x, screenHeight);
	}

	GLdouble _y = static_cast<GLdouble>(screenHeight) / 2.0 - static_cast<GLdouble>(y);

	room.updateCamera((_x / static_cast<GLdouble>(screenWidth) * 2.0), (_y / static_cast<GLdouble>(screenHeight) / 2.0));
}