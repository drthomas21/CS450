#include "tank.h"
#include "lib.h"

void Tank::setX(double x) {
	this->centerX = x;
}

void Tank::setY(double y) {
	this->centerY = y;
}

void Tank::setTurrentDegree(double d) {
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

double Tank::getTurrentTipX() {
	GLdouble scale = 10.0;
	float turrentRadius = 2.5;

	return (this->centerX + 0.5) + turrentRadius * cos(this->turrentDegree) * scale;
}

double Tank::getTurrentTipY() {
	GLdouble scale = 10.0;
	float turrentRadius = 2.5;
	float height = 1.5;

	return (this->centerY + height * 0.5 * scale) + turrentRadius * sin(this->turrentDegree) * scale;
}

void Tank::draw() {
	GLdouble scale = 10.0;
	float wheelRadius = 1.5;
	float turrentRadius = 2.5;
	float height = 1.5;
	float width = 2.0;

	//Turrent
	glColor3f(0.0f / 255.0f, 51.0f / 255.0f, 17.0f / 255.0f);
	glLineWidth(2.5);
	glBegin(GL_LINE_LOOP);
	glVertex2d((this->centerX + 0.5), (this->centerY + height * 0.5 * scale));
	glVertex2d((this->centerX + 0.5) + turrentRadius * cos(this->turrentDegree) * scale, (this->centerY + height * 0.5 * scale) + turrentRadius * sin(this->turrentDegree) * scale);
	glEnd();

	//Body
	glColor3f(0.0f / 255.0f, 102.0f / 255.0f, 34.0f / 255.0f);
	glBegin(GL_POLYGON);
	glVertex2d(this->centerX - width*scale, this->centerY - height*scale);
	glVertex2d(this->centerX + width*scale, this->centerY - height*scale);
	glVertex2d(this->centerX + (width*0.5)*scale, this->centerY + height*scale);
	glVertex2d(this->centerX - (width*0.5)*scale, this->centerY + height*scale);
	glEnd();

	glColor3f(10.0f / 255.0f, 10.0f / 255.0f, 10.0f / 255.0f);
	//Wheel 1
	glBegin(GL_POLYGON);
	for (double t = 0.0; t < 1.0; t += 0.005) {
		GLfloat x = static_cast<float>((this->centerX - 1.0*scale) + (wheelRadius * (float)PI) * cos(2.0 * PI * t));
		GLfloat y = static_cast<float>((this->centerY - height*scale) + (wheelRadius * (float)PI) * sin(2.0 * PI * t));
		glVertex2d(x, y);
	}
	glEnd();

	//Wheel 2
	glBegin(GL_POLYGON);
	for (double t = 0.0; t < 1.0; t += 0.005) {
		GLfloat x = static_cast<float>((this->centerX + 1.0*scale) + (wheelRadius * (float)PI) * cos(2.0 * PI * t));
		GLfloat y = static_cast<float>((this->centerY - height*scale) + (wheelRadius * (float)PI) * sin(2.0 * PI * t));
		glVertex2d(x, y);
	}
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
