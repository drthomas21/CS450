#include <windows.h>
#include <iostream>
#include <ctime>
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"
#include "bullet.h"
#include "tank.h"
#include "target.h"
#include "lib.h"

#include <iostream>
#include <cmath>
#include <fstream>

const int screenWidth = 600;
const int screenHeight = 600;

void setWindow(float, float, float, float);

void myInit();
void myIdle();
void myDisplay();
void myKeyboard(unsigned char, int, int);
void mySpecialKeyboard(int, int, int);

void drawGround();

Bullet bullet;
Tank tank;
Target target;

int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw callback function
	glutIdleFunc(myIdle);			// register idle callback function
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);

	//Random location for tank
	tank.setX(rand() % screenWidth);
	tank.setY(25.0);

	//Random location for target
	target.setX(rand() % screenWidth);
	target.setY((rand() % (screenHeight - 50)) + 50.0);

	bullet.setGroundLevel(20);

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
	glMatrixMode(GL_PROJECTION);			// set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

void myDisplay() {
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT);

	drawGround();
	tank.draw();
	target.draw();

	if (bullet.wasFired()) {
		bullet.draw();
	}

	glutSwapBuffers();	// send all output to display
}

void myIdle() {
	if (bullet.wasFired()) {
		bullet.incrTime();
		glutPostRedisplay();
	}	
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	double value;
	switch (theKey) {
		case 'a':
		case 'A':
			value = tank.getX() - 10.0;
			tank.setX(value >= 0.0 ? value : 0.0);
			break;
		case 'd':
		case 'D':
			value = tank.getX() + 10.0;
			tank.setX(value <= (double)screenWidth ? value : (double)screenWidth);
			break;

		case 'w':
		case 'W':
			value = tank.getTurrentDegree() + PI / 20.0;
			tank.setTurrentDegree(value <= PI ? value : PI);
			break;
		case 's':
		case 'S':
			value = tank.getTurrentDegree() - PI / 20.0;
			tank.setTurrentDegree(value >= 0.0 ? value : 0.0);
			break;
		case ' ':
			if (bullet.wasFired()) {
				break;
			}
			bullet.setX(tank.getTurrentTipX());
			bullet.setY(tank.getTurrentTipY());
			bullet.setTheta(tank.getTurrentDegree());
			bullet.fireBullet();
			break;
		default:
			std::cout << "theKey: " << theKey << std::endl;
			break;
	}

	glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY) {
	std::cout << "thSpecialeKey: " << theKey << std::endl;
}

void drawGround() {
	glColor3f(255.0/255.0, 153.0/255.0, 0.0/255.0);
	glBegin(GL_POLYGON);
	glVertex2d(0,0);
	glVertex2d(screenWidth, 0);
	glVertex2d(screenWidth, 20.0);
	glVertex2d(0, 20.0);
	glEnd();
}