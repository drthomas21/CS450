//Computer Graphics Lab - Animation

#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "gl/glut.h"

#include <iostream>
#include <cmath>
#include <fstream>

#include "Lab3.h"

std::vector<GLfloatPoint2D> orgShapeW;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);      // background color is white
	glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue
	setWindow(-worldWidth / 2, worldWidth / 2, -worldHeight / 2, worldHeight / 2); // replaces the following three lines

	//glMatrixMode(GL_PROJECTION); 	    // set "camera shape"
	//glLoadIdentity();
	//gluOrtho2D(-worldWidth,worldWidth,-worldHeight, worldHeight);


	line[0].x = 0;
	line[0].y = 0;
	line[1].x = 100;
	line[1].y = 0;
	lineLength = computeLineLength(line[0], line[1]);
	loadShapeFromFile(pathForShapeV, &shapeV);
	loadShapeFromFile(pathForShapeW, &shapeW);

	for (std::_Vector_iterator < std::_Vector_val < std::_Simple_types<GLfloatPoint2D> > > p = shapeW.begin(); p != shapeW.end(); p++) {
		orgShapeW.push_back(*p);
	}

	glLineWidth(3);
	glPointSize(3);
}

void myIdle()
{
	//this function will be invoked when idle

	t += 0.001;
	if (t >1) t = 0;

	GLfloatPoint2D point;

	point = orgShapeW[0];
	point.x = orgShapeW[0].x * (t) + shapeV[0].x * (1 - t);
	point.y = orgShapeW[0].y * (t) + shapeV[0].y * (1 - t);
	shapeW[0] = point;

	point = orgShapeW[1];
	point.x = orgShapeW[1].x * (t) + shapeV[0].x * (1 - t);
	point.y = orgShapeW[1].y * (t) + shapeV[0].y * (1 - t);
	shapeW[1] = point;

	point = orgShapeW[2];
	point.x = orgShapeW[2].x * (t) + shapeV[0].x * (1 - t);
	point.y = orgShapeW[2].y * (t) + shapeV[0].y * (1 - t);
	shapeW[2] = point;

	point = orgShapeW[3];
	point.x = orgShapeW[3].x * (t) + shapeV[1].x * (1 - t);
	point.y = orgShapeW[3].y * (t) + shapeV[1].y * (1 - t);
	shapeW[3] = point;

	point = orgShapeW[4];
	point.x = orgShapeW[4].x * (t) + shapeV[2].x * (1 - t);
	point.y = orgShapeW[4].y * (t) + shapeV[2].y * (1 - t);
	shapeW[4] = point;

	point = orgShapeW[5];
	point.x = orgShapeW[5].x * (t) + shapeV[3].x * (1 - t);
	point.y = orgShapeW[5].y * (t) + shapeV[3].y * (1 - t);
	shapeW[5] = point;

	point = orgShapeW[6];
	point.x = orgShapeW[6].x * (t) + shapeV[4].x * (1 - t);
	point.y = orgShapeW[6].y * (t) + shapeV[4].y * (1 - t);
	shapeW[6] = point;

	point = orgShapeW[7];
	point.x = orgShapeW[7].x * (t) + shapeV[4].x * (1 - t);
	point.y = orgShapeW[7].y * (t) + shapeV[4].y * (1 - t);
	shapeW[7] = point;

	point = orgShapeW[8];
	point.x = orgShapeW[8].x * (t) + shapeV[4].x * (1 - t);
	point.y = orgShapeW[8].y * (t) + shapeV[4].y * (1 - t);
	shapeW[8] = point;

	point = orgShapeW[9];
	point.x = orgShapeW[9].x * (t) + shapeV[5].x * (1 - t);
	point.y = orgShapeW[9].y * (t) + shapeV[5].y * (1 - t);
	shapeW[9] = point;

	//line[1].x = lineLength * cos(2 * PI*t);
	//line[1].y = lineLength * sin(2 * PI*t);

	glutPostRedisplay();
}

void drawW() {
	GLdouble scale = 300.0;
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_POINTS);
	for (size_t i = 0; i< shapeW.size(); i++) {
		GLfloatPoint2D point = shapeW[i];
		glVertex2d((point.x - 0.5)*scale, (point.y - 0.5)*scale);
	}
	glEnd();
}

void drawV() {
	GLdouble scale = 300.0;
	glBegin(GL_LINE_LOOP);
	for (size_t i = 0; i< shapeV.size(); i++) {
		GLfloatPoint2D point = shapeV[i];
		glVertex2d((point.x - 0.5)*scale, (point.y - 0.5)*scale);
	}
	glEnd();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	Sleep(1);
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	//glBegin(GL_LINES);
	//draw shape here
	//glVertex2f(line[0].x, line[0].y);
	//glVertex2f(line[1].x, line[1].y);
	//glEnd();

	drawW();

	glutSwapBuffers();	// send all output to display
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 150); // set window position on screen
	glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

	glutDisplayFunc(myDisplay);     // register redraw callback function
	glutIdleFunc(myIdle);			// register idle callback function

	myInit();
	glutMainLoop(); 		     // go into a perpetual loop
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

// Returns TRUE if file is successfully read otherwise returns FALSE
GLboolean loadShapeFromFile(string source, vector<GLfloatPoint2D>* shape) {
	ifstream myfile(source);
	if (myfile.is_open())
	{
		string line;    // String to hold
		GLfloat minX = std::numeric_limits<float>::infinity();
		GLfloat maxX = std::numeric_limits<float>::lowest();
		GLfloat minY = std::numeric_limits<float>::infinity();
		GLfloat maxY = std::numeric_limits<float>::lowest();
		while (getline(myfile, line))
		{
			string::size_type sz;
			GLfloat xCoord = std::stof(line, &sz);
			GLfloat yCoord = std::stof(line.substr(sz));
			GLfloatPoint2D newPoint;
			newPoint.x = xCoord;
			newPoint.y = yCoord;
			shape->push_back(newPoint);

			if (xCoord > maxX) {
				maxX = xCoord;
			}
			else if (xCoord < minX) {
				minX = xCoord;
			}

			if (yCoord > maxY) {
				maxY = yCoord;
			}
			else if (yCoord < minY) {
				minY = yCoord;
			}
		}
		myfile.close();

		for (size_t i = 0; i<shape->size(); i++) {
			(*shape)[i].x = ((*shape)[i].x - minX) / (maxX - minX);
			(*shape)[i].y = ((*shape)[i].y - minY) / (maxY - minY);
		}
	}
	else {
		cout << "Unable to open file";
		return false;
	}
	return true;
}