#include <windows.h>
#include <ctime>
#include <math.h>
#include <gl/Gl.h>
#include "gl/glut.h"
#define PI 3.14159265

// Used for saving x and y position of a point
struct GLintPoint {
	GLint x, y;
};

struct GL3DPoint {
	GLfloat x, y, z;
};

const int screenWidth = 500, screenHeight = 500, pointLimit = 5;
enum Keypress { KEYPRESS_S, KEYPRESS_NILL };
int keyboardKey = KEYPRESS_NILL, pPointer = 0;
bool resetOnInput = false, isPolygonFilled = false;
GL3DPoint fg, bg;
GLintPoint *points = nullptr; // Array for storing pentagon points

void clearPointer() {
	if (points != nullptr) {
		delete[] points;
	}
	pPointer = 0;
	points = new GLintPoint[pointLimit];
	isPolygonFilled = false;
}

void clearKeyboardPress() {
	if (keyboardKey != KEYPRESS_NILL) {
		keyboardKey = KEYPRESS_NILL;
	}
}

void myInit(void) {
	clearPointer();
	bg.x = 1, bg.y = 1, bg.z = 1;
	fg.x = 0, fg.y = 0, fg.z = 0;
	glClearColor(bg.x, bg.y, bg.z, 0.0);		// background color is white
	glColor3f(fg.x, fg.y, fg.z);			// drawing color is black
	glMatrixMode(GL_PROJECTION);			// set "camera shape"
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv) {
	srand((unsigned)time(0));
	glutInit(&argc, argv);												// initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// set display mode
	glutInitWindowSize(screenWidth, screenHeight);// set window size
	glutInitWindowPosition(100, 150);							// set window position on screen
	glutCreateWindow("Computer Graphics - Lab1");	// open the screen window

	//Anonymous functions to prevent direct call by programmer(s)
	glutDisplayFunc([](void) {
		// clear the screen
		glColor3f(fg.x, fg.y, fg.z);
		glClearColor(bg.x, bg.y, bg.z, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);		

		if (keyboardKey == KEYPRESS_S) {
			glBegin(GL_LINE_STRIP);
			GLint sets = 2;
			GLdouble incr = PI / 1000;
			GLdouble A = screenWidth / (PI * sets), B = 0.0, C = screenHeight / 2.0, D = C;

			for (GLdouble x = 0; x < PI*sets; x += incr) {
				GLdouble func = sin(x);
				glVertex2d(A * x + B, C * func + D);
			}
			glEnd();
		} else if (pPointer > 0) {
			if (pPointer == pointLimit) {
				if (isPolygonFilled) {
					glBegin(GL_POLYGON);
				} else {
					glBegin(GL_LINE_LOOP);
				}
			} else if(pPointer > 1) {
				glBegin(GL_LINE_STRIP);
			} else {
				glBegin(GL_POINTS);
			}

			for (int i = 0; i < pPointer; i++) {
				glVertex2d(points[i].x, points[i].y);
			}
			glEnd();
		}

		glFlush();
	});		// register redraw function

	glutMouseFunc([](int button, int state, int x, int y) {
		if (state == GLUT_DOWN) {
			if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON ) {
				clearKeyboardPress();
				if (resetOnInput && button == GLUT_LEFT_BUTTON) {
					clearPointer();
					resetOnInput = false;
				}

				if (button == GLUT_RIGHT_BUTTON) {
					resetOnInput = true;
				}

				if (pPointer >= pointLimit || (pPointer < pointLimit - 1 && button == GLUT_RIGHT_BUTTON)) {
					return;
				}

				GLintPoint point;
				point.x = x;
				point.y = screenHeight - y;
				points[pPointer] = point;
				pPointer++;

				glutPostRedisplay();
			}
		}
	});				// register mouse callback function
	glutKeyboardFunc([](unsigned char theKey, int mouseX, int mouseY) {
		switch (theKey) {
			case 'b':
				bg.x = ((double)(rand() % 256) / 256.0);
				bg.y = ((double)(rand() % 256) / 256.0);
				bg.z = ((double)(rand() % 256) / 256.0);
				break;
			case 'f':
				fg.x = ((double)(rand() % 256) / 256.0);
				fg.y = ((double)(rand() % 256) / 256.0);
				fg.z = ((double)(rand() % 256) / 256.0);
				break;
			case 's':
				bg.x = 1;
				bg.y = 1;
				bg.z = 1;
				clearPointer();
				keyboardKey = KEYPRESS_S;
				break;
			case 't':
				isPolygonFilled = !isPolygonFilled;
				break;
			default:
				break;		      // do nothing
		}

		glutPostRedisplay();
	});	// register keyboard callback function

	myInit();

	glutMainLoop();		// go into a perpetual loop
}

/* C++ code segment to generate random numbers:

#include <ctime>

...

srand((unsigned)time(0));
int randomInt = rand()%50 + 1;
float randomFloat = (float)rand()/RAND_MAX;
cout << "Random Integer between 1 and 50 = " << randomInt << endl;
cout << "Random Float between 0 and 1 = " << randomFloat << endl;
*/