#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "target.h"
#include "lib.h"

void Target::setX(double x) {
	this->centerX = x;
}

void Target::setY(double y) {
	this->centerY = y;
}

double Target::getX() {
	return this->centerX;
}

double Target::getY() {
	return this->centerY;
}

void Target::draw() {
	//GLdouble scale = 300.0;
	glPointSize(2.0);
	glColor3f(1.0f, 0.1f, 0.1f);
	glBegin(GL_POINT);
	glVertex2d(this->centerX, this->centerY);
	glEnd();
}

Target::Target() :centerX(0.0), centerY(0.0) { }
Target Target::operator=(const Target &source) {
	Target instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}