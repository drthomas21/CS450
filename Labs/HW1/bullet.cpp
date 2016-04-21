#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "bullet.h"
#include "lib.h"

void Bullet::setX(double x) {
	this->centerX= x;
}

void Bullet::setY(double y) {
	this->centerY = y;
}

double Bullet::getX() {
	return this->centerX;
}

double Bullet::getY() {
	return this->centerY;
}

void Bullet::draw() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2.0);
	glBegin(GL_POINT);
	glVertex2d(this->centerX, this->centerY);
	glEnd();
}

Bullet::Bullet() :centerX(0.0), centerY(0.0) { }
Bullet Bullet::operator=(const Bullet &source) {
	Bullet instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}