#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <math.h>
#include <iostream>
#include "target.h"
#include "lib.h"
#define VELOCITY 220.0

FILETIME ft;
long long time = 0;

void Target::setX(double x) {
	this->centerX = x;
}

void Target::setY(double y) {
	this->centerY = y;
}

void Target::flipVelocityX() {
	this->xFactor *= -1;
}

void Target::flipVelocityY() {
	this->yFactor *= -1;
}

void Target::toggleMovement() {
	this->moving = !this->moving;
}

void Target::checkCollision(const Bullet &bullet) {
	double x = this->getX() - bullet.getX();
	double y = this->getY() - bullet.getY();
	double d = pow((x * x) + (y * y),0.5) - this->RADIUS - bullet.RADIUS;
	if (d <= 0.0) {
		std::cout << "collision" << std::endl;
	}
}

void Target::calculatePosition() {
	if (time == 0) {
		GetSystemTimeAsFileTime(&ft);
		time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	} else {
		long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - time; //nanoseconds
		double incr = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

		this->centerX += this->xFactor * (VELOCITY * cos(this->theta));
		this->centerX += this->yFactor * (VELOCITY * sin(this->theta));
	}	
}

double Target::getX() const {
	return this->centerX;
}

double Target::getY() const {
	return this->centerY;
}

bool Target::isMoving() {
	return this->moving;
}

void Target::draw() {
	glColor3f(1.0f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
	for (double t = 0.0; t < 1.0; t += 0.005) {
		GLfloat x = static_cast<float>((this->centerX) + (this->RADIUS * (float)PI) * cos(2.0 * PI * t));
		GLfloat y = static_cast<float>((this->centerY) + (this->RADIUS * (float)PI) * sin(2.0 * PI * t));
		glVertex2d(x, y);
	}
	glEnd();
}

Target::Target() :centerX(0.0), centerY(0.0), xFactor(1.0), yFactor(1.0), moving(true) { this->theta = ((double)(rand() % (360))) * (PI/180.0); }
Target Target::operator=(const Target &source) {
	Target instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}