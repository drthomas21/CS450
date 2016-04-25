#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "target.h"
#include "lib.h"
#define VELOCITY_X 200.0
#define VELOCITY_Y 200.0

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
	float radius = 3.0;

	glColor3f(1.0f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
	for (double t = 0.0; t < 1.0; t += 0.005) {
		GLfloat x = static_cast<float>((this->centerX) + (radius * (float)PI) * cos(2.0 * PI * t));
		GLfloat y = static_cast<float>((this->centerY) + (radius * (float)PI) * sin(2.0 * PI * t));
		glVertex2d(x, y);
	}
	glEnd();
}

Target::Target() :centerX(0.0), centerY(0.0) { }
Target Target::operator=(const Target &source) {
	Target instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}