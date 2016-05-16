#ifdef _WIN32
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"
#elif __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/Gl.h>
#include <GLUT/GLUT.h>
#endif

#include <iostream>

#include "Lab5.h"
#include "SpaceObject.h"

SpaceObject Sun;
SpaceObject Earth;
SpaceObject Moon;
SpaceObject Mars;
bool toggleCameraRotate = false;
double i = 0;

void myInit(int, int);
void myIdle();
void displaySolarSystem();
void myKeyboard(unsigned char, int, int);

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv) {
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Inner Solar System"); // open the screen window


	int shadingChoice = 0;
	int colorChoice = 0;
	std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n";
	std::cin >> shadingChoice;

	std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n";
	std::cin >> colorChoice;

	//Sun - 0.5, 20, 16
	Sun.setX(0);
	Sun.setY(0);
	Sun.setZ(0);
	Sun.toggleOrbit();
	Sun.setRadius(0.5);
	Sun.setSlices(20);
	Sun.setStacks(16);
	Sun.setRotate(15);
	Sun.setRotateVectorX(0);
	Sun.setRotateVectorY(1.0);
	Sun.setRotateVectorZ(0);
	Sun.setScale(scale);

	//Earth - 0.2, 20, 8
	Earth.setParent(&Sun);
	Earth.setX(2);
	Earth.setY(0);
	Earth.setZ(0);
	Earth.setRadius(0.2);
	Earth.setSlices(20);
	Earth.setStacks(8);
	Earth.setOrbitRadiusX(2.5);
	Earth.setOrbitRadiusY(1.5);
	Earth.setOrbitRadiusZ(2);
	Earth.setOrbitSpeed(0.01);
	Earth.setRotate(26);
	Earth.setRotateVectorX(0);
	Earth.setRotateVectorY(1);
	Earth.setRotateVectorZ(0);
	Earth.setScale(scale);

	//Moon - 0.05, 10, 4
	Moon.setParent(&Earth);
	Moon.setX(-0.5);
	Moon.setY(0);
	Moon.setZ(0);
	Moon.setRadius(0.05);
	Moon.setSlices(10);
	Moon.setStacks(4);
	Moon.setOrbitRadiusX(0.5);
	Moon.setOrbitRadiusY(0.7);
	Moon.setOrbitRadiusZ(0.57);
	Moon.setOrbitSpeed(-0.03);
	Moon.setRotate(31);
	Moon.setRotateVectorX(0);
	Moon.setRotateVectorY(1);
	Moon.setRotateVectorZ(0);
	Moon.setScale(scale);

	//Mars - 0.15, 20, 8
	Mars.setParent(&Sun);
	Mars.setX(-3);
	Mars.setY(0);
	Mars.setZ(0);
	Mars.setRadius(0.15);
	Mars.setSlices(20);
	Mars.setStacks(8);
	Mars.setOrbitRadiusX(1.5);
	Mars.setOrbitRadiusY(3.5);
	Mars.setOrbitRadiusZ(4);
	Mars.setOrbitSpeed(-0.01);
	Mars.setRotate(22);
	Mars.setRotateVectorX(0);
	Mars.setRotateVectorY(1);
	Mars.setRotateVectorZ(0);
	Mars.setScale(scale);

	myInit(shadingChoice, colorChoice);

	glutDisplayFunc(displaySolarSystem);
	glutIdleFunc(myIdle);
	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return(0);
}

void myInit(int shadingChoice, int colorChoice) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	if (shadingChoice == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	else if (shadingChoice == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	}

	if (colorChoice == 1) {
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-3.5*worldWidth / worldHeight, 3.5*worldWidth / worldHeight, -3.5, 3.5, 0.1, 100);
}

void myIdle() {
	Sun.animate();
	Earth.animate();
	Moon.animate();
	Mars.animate();

	if (toggleCameraRotate) {
		i += 0.0001;
		eyex = 25.0 * sin(2 * PI * i);
		eyez = 50.0 * cos(2 * PI * i);
		if (i >= 1) {
			i = 0;
		}
	}

	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem() {
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

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

	// Sun
	glColor3f(1.0f, 0.5f, 0.0f);    // sun is orange
	Sun.draw();

	// Earth
	glColor3f(0.0f, 1.0f, 0.0f); // earth is green
	Earth.draw();

	// Moon
	glColor3f(0.5f, 0.5f, 0.5f);
	Moon.draw();

	// Mars
	glColor3f(1.0f, 0.0f, 0.0f);
	Mars.draw();

	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'V':
	case 'v':
		view = (view + 1) % 3;
		if (view == 0) {
			eyex = 25;
			eyey = 25;
			eyez = 25;
		}
		else if (view == 1) {
			eyex = 25;
			eyey = 0;
			eyez = 0;
		}
		else if (view == 2) {
			eyex = 0;
			eyey = 25;
			eyez = 25;
		}
		break;
	case 'R':
	case 'r':
		toggleCameraRotate = !toggleCameraRotate;
		break;
	default:
		break;
	}

	glutPostRedisplay();

}