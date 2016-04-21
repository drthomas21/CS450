#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#include <vector>
#include <string>

#define PI 3.1415

using namespace std;

struct GLintPoint2D {
	GLint x, y;
};

struct GLfloatPoint2D {
	GLfloat x, y;
};


//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;

GLfloatPoint2D line[2];
GLdouble lineLength;

// Initial values
GLdouble t = 0.0;


// Vectors to hold points for shapes
vector<GLfloatPoint2D> shapeV;
vector<GLfloatPoint2D> shapeW;

// Paths for shape files
string pathForShapeV = "./V.txt";
string pathForShapeW = "./W.txt";


void setWindow(float left, float right, float bottom, float top);
float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2);
GLboolean loadShapeFromFile(string source, vector<GLfloatPoint2D>* shape);

#endif