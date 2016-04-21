#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include "gl/glut.h"
#include <iostream>
#define PI 3.14159265

// screen window size
const int screenWidth = 500;
const int screenHeight = 500;
const int viewShift = 1;

// left, right, bottom, top of the world window
float lt, rt, bt, tp;
bool tToggle = true;
GLfloat lineWeight = 1.0;
int choice = 0, radius = 1, height = 1, width = 1;
enum Choices {CIRCLE = 1, ELLIPTICAL};

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLineWidth(lineWeight);
	glLoadIdentity();
	lt = -10;
	rt = 10;
	bt = -10;
	tp = 10;
	gluOrtho2D(lt, rt, bt, tp);	// set the world window
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv) {
	glutInit(&argc, argv);          // initialize the toolkit
									//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics - Lab"); // open the screen window

	// register redraw function
	glutDisplayFunc([] (void){
		glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

		if (tToggle) {
			glBegin(GL_LINE_LOOP);
		} else {
			glBegin(GL_POINTS);
		}		
		
		// draw a shape
		switch (choice) {
			case(CIRCLE) :
				for (float i = 0.0; i < 1.0; i += 0.001) {
					GLfloat x = 0.0 + ((float)radius) * cos(2.0 * PI * i);
					GLfloat y = 0.0 + ((float)radius) * sin(2.0 * PI * i);
					glVertex2f(x, y);
				}
				break;
			case(ELLIPTICAL) :
				for (float i = 0.0; i < 1.0; i += 0.001) {
					GLfloat x = 0.0 + (float)width * cos(2 * PI * i);
					GLfloat y = 0.0 + (float)height * sin(2 * PI * i);
					glVertex2d(x, y);
				}
				break;
		}

		glEnd();

		glutSwapBuffers();
	}); 

	glutKeyboardFunc([](unsigned char theKey, int mouseX, int mouseY) {
		switch (theKey) {
		case 'z':
			if (tp - viewShift < bt + viewShift) {
				break;
			}
			// zoom-in
			tp -= viewShift;
			bt += viewShift;
			lt += viewShift;
			rt -= viewShift;
			std::cout << "zoom-in" << std::endl;
			break;
		case 'Z':
			// zoom-out
			tp += viewShift;
			bt -= viewShift;
			lt -= viewShift;
			rt += viewShift;
			std::cout << "zoom-out" << std::endl;
			break;
		case 't':
			tToggle = true;
			std::cout << "switch to line" << std::endl;
			break;
		case 'T':
			tToggle = false;
			std::cout << "switch to points" << std::endl;
			break;
		case '+':
			if (choice == CIRCLE) {
				radius += 1;
				std::cout << "increase radius" << std::endl;
			} else {
				height += 1;
				width += 1;
				std::cout << "increase width & height" << std::endl;
			}

			break;
		case '-':
			if (choice == CIRCLE && radius > 1) {
				radius -= 1;
				std::cout << "decrease radius" << std::endl;
			} else if(width > 1 && height > 1) {
				height -= 1;
				width -= 1;
				std::cout << "decrease width & height" << std::endl;
			}
			break;
		case 'b':
			lineWeight += 0.5;
			std::cout << "increase line weight" << std::endl;
			break;
		case 'B':
			lineWeight -= 0.5;
			std::cout << "decrease line weight" << std::endl;
			break;
		default:
			break;		      // do nothing
		}
		glLineWidth(lineWeight);
		glPointSize(lineWeight);
		setWindow(lt, rt, bt, tp);
		glutPostRedisplay(); // implicitly call myDisplay
	});

	glutSpecialFunc([](int theKey, int mouseX, int mouseY) {
		switch (theKey) {
		case GLUT_KEY_UP:
			// move the object to the top in a small amount
			tp -= viewShift;
			bt -= viewShift;
			std::cout << "key up" << std::endl;
			break;
		case GLUT_KEY_DOWN:
			// move the object to the bottom in a small amount
			tp += viewShift;
			bt += viewShift;
			std::cout << "key down" << std::endl;
			break;
		case GLUT_KEY_LEFT:
			// move the object to the left in a small amount
			lt += viewShift;
			rt += viewShift;
			std::cout << "key left" << std::endl;
			break;
		case GLUT_KEY_RIGHT:
			// move the object to the right in a small amount
			lt -= viewShift;
			rt -= viewShift;
			std::cout << "key right" << std::endl;
			break;
		default:
			break;		      // do nothing
		}
		setWindow(lt, rt, bt, tp);
		glutPostRedisplay(); // implicitly call myDisplay
	});

	std::cout << CIRCLE << ". Drawing a circle" << std::endl << ELLIPTICAL << ". Drawing an ellipse" << std::endl << "Choose 1 or 2: " << std::endl;
	std::cin >> choice;

	switch (choice) {
		case(CIRCLE) :
			std::cout << "Radius: ";
			std::cin >> radius;
			break;
		case(ELLIPTICAL) :
			std::cout << "Height: ";
			std::cin >> height;
			std::cout << "Width: ";
			std::cin >> width;
	}

	myInit();

	glutMainLoop(); 		     // go into a perpetual loop
	return 0;
}