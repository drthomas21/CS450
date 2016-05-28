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

#include "Lab-Camera.h"
GLdouble x = 0, y = 0, z = 0, r = 0, lightSX = 0, lightSY = 0, lightSZ = 0;
GLfloat position[] = { 3,5,3, 0.0f };
GLfloat lightIntensity[] = { 0.9f, 0.9f, 0.9f, 1.0f };
long long time = 0;
bool toggleLightAnimation = false;

//<<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>>>
void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
	glColor3f(1.0f, 1.0f, 1.0f);    // drawing color is white

	

	// set the view volume shape ----
	cam.setShape(50.0f, 64.0f / 48.0f, 0.5f, 200.0f);
	//---------------------------

	//make the initial camera
	cam.set(Point3(4, 4, 4), Point3(0, 0, 0), Vector3(0, 1, 0));

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// place the light
	GLfloat litePos[] = { 0, 10, 0, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, litePos);
	// define some colors
	GLfloat amb0[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diff0[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat spec0[] = { 1.0, 1.0, 1.0, 1.0 };
	// attach them to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch (theKey)
	{
	case GLUT_KEY_LEFT:
		std::cout << "Camera move left" << std::endl;
		cam.slide(-0.2, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		std::cout << "Camera move right" << std::endl;
		cam.slide(0.2, 0, 0);
		break;
	case GLUT_KEY_UP:
		std::cout << "Camera move up" << std::endl;
		cam.slide(0, 0.2, 0);
		break;
	case GLUT_KEY_DOWN:
		std::cout << "Camera move down" << std::endl;
		cam.slide(0, -0.2, 0);
		break;
	case GLUT_KEY_PAGE_UP:
		// slide camera forward
		std::cout << "Camera zoom-in" << std::endl;
		cam.slide(0, 0, -0.2);
		break;
	case GLUT_KEY_PAGE_DOWN:
		// slide camera backward
		std::cout << "Camera zoom-out" << std::endl;
		cam.slide(0, 0, 0.2);
		break;
	default:
		break;
	}
	glutPostRedisplay(); // draw it again
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A':
		std::cout << "Toggle animation" << std::endl;
		toggleLightAnimation = !toggleLightAnimation;
		if (toggleLightAnimation) {
			FILETIME ft;
			GetSystemTimeAsFileTime(&ft);
			time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
		}
		break;
	case 'r':
		std::cout << "Camera roll counter clock-wise " << std::endl;
		cam.roll(1.0);
		break; // roll the camera 
	case 'R':
		std::cout << "Camera roll clock-wise" << std::endl;
		cam.roll(-1.0);
		break; // roll the camera back	
	case 'p':
		std::cout << "Camera pitch up" << std::endl;
		cam.pitch(1.0);
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break;
	case 'P':
		std::cout << "Camera pitch down" << std::endl;
		cam.pitch(-1.0);
		// complete pitch function in camera.cpp and invoke cam.pitch() function
		break;
	case 'y':
		std::cout << "Camera yaw left" << std::endl;
		cam.yaw(1.0);
		// complete yaw function in camera.cpp and invoke cam.yaw() function
		break;
	case 'Y':
		std::cout << "Camera yaw right" << std::endl;
		cam.yaw(-1.0);
		// complete yaw function in camera.cpp and invoke cam.yaw() function
		break;
	case 'w':
		std::cout << "Teapot shifted right" << std::endl;
		x += -1;
		z += -1;
		break;
	case 'W':
		std::cout << "Teapot shifted left" << std::endl;
		x += 1;
		z += 1;
		break;
	case 'e':
		std::cout << "Teapot rotated left" << std::endl;
		r += -1.0;
		break;
	case 'E':
		std::cout << "Teapot rotated right" << std::endl;
		r += 1.0;
		break;


	default:
		break;
	}
	glutPostRedisplay(); // draw it again
}


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void) {
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat mat[4], ambr, ambg, ambb, difr, difg, difb, specr, specg, specb, shine;
	
	glPushMatrix();
		//glTranslated(lightSX, lightSY, lightSZ);
		position[0] = lightSX;
		position[2] = lightSZ;
		glLightfv(GL_LIGHT0, GL_POSITION, position);

	glPopMatrix();

	glPushMatrix();
		ambr = 0.24725, ambg = 0.1995, ambb = 0.0745;
		difr = 0.75164, difg = 0.60648, difb = 0.22648;
		specr = 0.628281, specg = 0.555802, specb = 0.366065;
		shine = 0.4;
		mat[0] = ambr;
		mat[1] = ambg;
		mat[2] = ambb;
		mat[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
		mat[0] = difr;
		mat[1] = difg;
		mat[2] = difb;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		mat[0] = specr;
		mat[1] = specg;
		mat[2] = specb;
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
		glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
		glColor3f(255.0 / 256.0, 215.0 / 256.0, 0.0 / 256.0);
		glTranslated(x - 2.0, y, z + 2.0);
		glRotated(r, 0, 1, 0);
		glutSolidTeapot(1.0); // draw the teapot
	glPopMatrix();

	glPushMatrix();
		ambr = 0.19225, ambg = 0.19225, ambb = 0.19225;
		difr = 0.50754, difg = 0.50754, difb = 0.50754;
		specr = 0.508273, specg = 0.508273, specb = 0.508273;
		shine = 0.4;
		mat[0] = ambr;
		mat[1] = ambg;
		mat[2] = ambb;
		mat[3] = 1.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
		mat[0] = difr;
		mat[1] = difg;
		mat[2] = difb;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		mat[0] = specr;
		mat[1] = specg;
		mat[2] = specb;
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
		glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
		glColor3f(192.0 / 256.0, 192.0 / 256.0, 192.0 / 256.0);
		glTranslated(x + 2.0, y, z - 2.0);
		glRotated(r, 0, 1, 0);
		glutSolidTeapot(1.0); // draw the teapot
	glPopMatrix();
	glutSwapBuffers();
}

void myIdle() {
	if (!toggleLightAnimation) return;

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - time; //nanoseconds
	double _time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)) * (0.2); //seconds

	while (_time > 1.0) {
		_time -= 1.0;
		time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}
	
	lightSX = 6.0 * cos(2.0 * 3.14 * _time);
	lightSZ= 6.0 * sin(2.0 * 3.14 * _time);
	glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab - Manipulate a camera around a teapot"); // open the screen window

																   // register callback functions
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);

	myInit();

	glutMainLoop();

	return(0);
}