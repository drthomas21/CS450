#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "gl/glut.h"
#include <iostream>
#define PI 3.14159265

using namespace std;

const int screenWidth = 640;
const int screenHeight = 480;

int choice = 0;

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv) {
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics - Lab"); // open the screen window

	glutDisplayFunc([](void) {
		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT);
		GLdouble A = screenWidth / 4.0; // set values used for scaling and shifting
		GLdouble B = 0.0;
		GLdouble C = screenHeight / 2.0;
		GLdouble D = C;

		// draw a graph here
		if (choice == 1) {
			glBegin(GL_LINE_STRIP);
			GLint sets = 2;
			GLdouble incr = PI / 1000;
			A = screenWidth / (PI * sets);
			for (GLdouble x = 0; x < PI*sets; x += incr) {
				GLdouble func = sin(x);
				glVertex2d( A * x + B, C * func + D);
			}
			glEnd();
		}
		else if (choice == 2) {
			glBegin(GL_LINE_STRIP);
			GLint sets = 4;
			GLdouble incr = PI / 1000;
			A = screenWidth / (PI * sets);
			for (GLdouble x = 0; x < PI * sets; x += incr) {
				GLdouble func = sin(x);
				glVertex2d(A * x + B, C * func + D);
			}
			glEnd();
		}
		else if (choice == 3) {
			glBegin(GL_LINE_STRIP);
			GLint sets = 6;
			GLdouble incr = PI / 1000;
			A = screenWidth / (PI * sets);
			for (GLdouble x = 0; x < PI * sets; x += incr) {
				GLdouble func = cos(x);
				glVertex2d(A * x + B, C * func + D);
			}
			glEnd();
		}
		else if (choice == 4) {
			glBegin(GL_LINE_LOOP);
			GLdouble centerX = screenWidth / 2.0;
			GLdouble centerY = screenHeight / 2.0;
			GLdouble scale = screenWidth / 6.0;
			glVertex2d((centerX - (scale * 2.0))	, (centerY + (scale * 0.0)));
			glVertex2d((centerX - (scale * 0.5))	, (centerY + (scale * 0.5)));
			glVertex2d((centerX - (scale * 0.0))	, (centerY + (scale * 2.0)));
			glVertex2d((centerX + (scale * 0.5))	, (centerY + (scale * 0.5)));
			glVertex2d((centerX + (scale * 2.0))	, (centerY + (scale * 0.0)));
			glVertex2d((centerX + (scale * 0.75))	, (centerY - (scale * 0.5)));
			glVertex2d((centerX + (scale * 1.0))	, (centerY - (scale * 2.0)));
			glVertex2d((centerX - (scale * 0.0))	, (centerY - (scale * 0.75)));
			glVertex2d((centerX - (scale * 1.0))	, (centerY - (scale * 2.0)));
			glVertex2d((centerX - (scale * 0.75))	, (centerY - (scale * 0.5)));
			glEnd();
		}
		glFlush();
	});     // register redraw function

	cout << "Enter an integer (1 -4 ) for your choice : ";
	cin >> choice;

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop
	return 0;
}