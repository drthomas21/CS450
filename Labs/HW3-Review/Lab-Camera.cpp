//Lab: Camera Control

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
#include "camera.h"

//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels
GLdouble x = 0, y = 0, z = 0, r = 0;

Camera cam; // global camera object

//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // background is white
	glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

									// set the view volume shape ----
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, 64.0f / 48.0f, 0.5f, 200000.0f);
	//---------------------------

	//make the initial camera
	cam.set(Point3(0,0,60000), Point3(-5,-10,5), Vector3(0, 1, 0));
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	/**/
	glColor3f(0.0f, 0.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(5000, 0, 0);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 5000, 0);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 5000);
	/**/
	glColor3f(0.5f, 0.5f, 1.0f);
	double t1 = -1000;
	double t = 10000;
	/*Question 1
	glVertex3f(1.0 + 2.0*t1, 1.0 + 3.0*t1, 10.0);
	glVertex3f(1.0+2.0*t,1.0+3.0*t,10.0);

	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-2.0 + 2.0*t1, 2.0 + 3.0*t1, 17.0);
	glVertex3f(-2.0 + 2.0*t, 2.0 + 3.0*t, 17.0);

	/*Question 2*/
	glVertex3f(1.0 + 2.0*t1, 1.0 + 3.0*t1, 12.0 - 2.0 * t1);
	glVertex3f(1.0 + 2.0*t, 1.0 + 3.0*t, 12.0 - 2.0 * t);

	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-2.0 + 2.0*t1, 2.0 + 3.0*t1, 17.0 - 2.0 * t1);
	glVertex3f(-2.0 + 2.0*t, 2.0 + 3.0*t, 17.0 - 2.0 * t);
	glEnd();
	/* */
	glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab - Manipulate a camera around a teapot"); // open the screen window

	glutDisplayFunc(myDisplay);

	myInit();

	glutMainLoop();

	return(0);
}