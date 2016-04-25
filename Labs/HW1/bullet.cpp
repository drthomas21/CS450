#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "bullet.h"
#include "lib.h"
#define GRAVITY 9.8
#define BULLET_VELOCITY 600.0

void Bullet::setX(double x) {
	this->centerX= x;
}

void Bullet::setY(double y) {
	this->centerY = y;
}

void Bullet::setTheta(double d) {
	this->theta = d;
}

void Bullet::setGroundLevel(double i) {
	this->groundLevel = i;
}

void Bullet::fireBullet() {
	this->fired = true;

	struct timeval time;
	gettimeofday(&time, NULL);

	this->time = time.tv_usec;
	this->_time = this->time;
}

void Bullet::hitTarget() {
	this->fired = false;
}

void Bullet::incrTime() {
	if (!this->fired) {
		return;
	}

	struct timeval _time;
	gettimeofday(&_time, NULL);

	long long diff = _time.tv_usec - this->time; //microseconds
	long long _diff = _time.tv_usec - this->_time; //microseconds
	double incr = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(1000000.0)); //seconds
	double time = static_cast<double>(static_cast<long double>(_diff) / static_cast<long double>(1000000.0)); //seconds
	std::cout << "incr: " << incr << std::endl;

	//Do Math
	this->centerX += BULLET_VELOCITY * cos(this->theta) * static_cast<double>(incr);
	this->centerY += BULLET_VELOCITY * sin(this->theta) * incr - 0.5 * GRAVITY * time * time;

	this->time += diff;

	std::cout << "Bullet: " << this->centerX << ", " << this->centerY << std::endl;

	//Check
	if (this->centerY <= this->groundLevel) {
		this->fired = false;
	}
}

bool Bullet::wasFired() {
	return this->fired;
}

double Bullet::getX() const {
	return this->centerX;
}

double Bullet::getY() const {
	return this->centerY;
}

void Bullet::draw() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (double t = 0.0; t < 1.0; t += 0.005) {
		GLfloat x = static_cast<float>((this->centerX) + (this->RADIUS * (float)PI) * cos(2.0 * PI * t));
		GLfloat y = static_cast<float>((this->centerY) + (this->RADIUS * (float)PI) * sin(2.0 * PI * t));
		glVertex2d(x, y);
	}
	glEnd();
}

Bullet::Bullet() :centerX(0.0), centerY(0.0), time(0), theta(0.0), groundLevel(0.0), fired(false) { }
Bullet Bullet::operator=(const Bullet &source) {
	Bullet instance;
	instance.centerX = source.centerX;
	instance.centerY = source.centerY;
	return instance;
}
