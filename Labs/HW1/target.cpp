#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "target.h"
#include "lib.h"
#define TARGET_VELOCITY 220.0

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
	if (!this->isConfigured) {
		gettimeofday(&this->time, NULL);
		this->isConfigured = true;
	} else {
		struct timeval _time;
		gettimeofday(&_time,NULL);
		long long diff = _time.tv_usec - this->time.tv_usec; //microseconds
		double incr = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

		this->centerX += this->xFactor * (TARGET_VELOCITY * cos(this->theta));
		this->centerX += this->yFactor * (TARGET_VELOCITY * sin(this->theta));

		this->time.tv_usec += diff;
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

Target::Target() :centerX(0.0), centerY(0.0), xFactor(1.0), yFactor(1.0), moving(true), isConfigured(false) { this->theta = ((double)(rand() % (360))) * (PI/180.0); }
Target Target::operator=(const Target &source) {
	Target instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}
