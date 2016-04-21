#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "tank.h"
#include "lib.h"

void Tank::setX(double x) {
	this->centerX = x;
}

void Tank::setY(double y) {
	this->centerY = y;
}

void Tank::setTurrentDegree(double d) {
	if (d > 0) {
		d = 0;
	}
	else if (d < (PI / 2.0)) {
		d = (PI / 2.0);
	}
	this->turrentDegree = d;
}

double Tank::getX() {
	return this->centerX;
}

double Tank::getY() {
	return this->centerY;
}

double Tank::getTurrentDegree() {
	return this->turrentDegree;
}

void Tank::draw() {
	GLdouble scale = 300.0;

	glColor3f(0.1f, 0.1f, 1.0f);
	//Body
	glBegin(GL_POLYGON);
	glVertex2d(this->centerX - 2.0*scale, this->centerY - 2.0*scale);
	glVertex2d(this->centerX + 2.0*scale, this->centerY - 2.0*scale);
	glVertex2d(this->centerX - 1.0*scale, this->centerY + 2.0*scale);
	glVertex2d(this->centerX + 1.0*scale, this->centerY + 2.0*scale);
	glEnd();

	//Wheel 1
	glBegin(GL_POLYGON);
	for (float t = 0; t < 1.0; t += 0.005) {
		GLfloat x = (this->centerX - 2.0*scale) + ((float)PI) * cos(2.0 * PI * t);
		GLfloat y = (this->centerY - 2.0*scale) + ((float)PI) * sin(2.0 * PI * t);
		glVertex2d(x, y);
	}
	glEnd();

	//Wheel 2
	glBegin(GL_POLYGON);
	for (float t = 0; t < 1.0; t += 0.005) {
		GLfloat x = (this->centerX - 2.0*scale) + ((float)PI) * cos(2.0 * PI * t);
		GLfloat y = (this->centerY + 2.0*scale) + ((float)PI) * sin(2.0 * PI * t);
		glVertex2d(x, y);
	}
	glEnd();

	//Turrent
	glBegin(GL_POLYGON);
	glVertex2d(this->centerX,this->centerY);
	glVertex2d((this->centerX + 0.5) * cos(this->turrentDegree), (this->centerY + 0.5) * sin(this->turrentDegree));
	glEnd();
}

Tank::Tank() :centerX(0.0), centerY(0.0), turrentDegree(0.0) { }
Tank Tank::operator=(const Tank &source) {
	Tank instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	instance.turrentDegree = source.turrentDegree;
	return instance;
}