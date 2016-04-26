#include <iostream>
#include <stdio.h>
#include "bullet.h"
#include "lib.h"

void Bullet::setX(double x) {
	this->centerX= x;
	this->_centerX = x;
}

void Bullet::setY(double y) {
	this->centerY = y;
	this->_centerY = y;
}

void Bullet::setVelocity(double v) {
	this->velocity = v;
}

void Bullet::setTheta(double d) {
	this->theta = d;
}

void Bullet::setGroundLevel(double i) {
	this->groundLevel = i;
}

void Bullet::fireBullet() {
	this->fired = true;

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);

	if (DEBUG_ENABLE_BULLET_PATH) this->bulletVector.clear();
}

void Bullet::hitTarget() {
	this->fired = false;
}

void Bullet::incrTime() {
	if (!this->fired) {
		return;
	}

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	//Do Math
	this->centerX = this->_centerX + this->velocity * cos(this->theta) * time;
	this->centerY = this->_centerY + this->velocity * sin(this->theta) * time - 0.5 * GRAVITY * time * time;

	if (DEBUG_ENABLE_BULLET) {
		double velocityY = this->velocity * sin(this->theta) - GRAVITY * time;
		double velocityX = this->velocity * cos(this->theta);

		std::cout << "Velocity X: " << velocityX << " | Velocity Y: " << velocityY << std::endl;
	}

	if (DEBUG_ENABLE_BULLET_PATH) {
		GLfloatPoint2D point;
		point.x = this->centerX;
		point.y = this->centerY;
		this->bulletVector.push_back(point);
	}

	if(DEBUG_ENABLE_BULLET) std::cout << "Bullet: " << this->centerX << ", " << this->centerY << std::endl;

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

double Bullet::getTheta() const {
	return this->theta;
}

double Bullet::getVelocity() const {
	return this->velocity;
}

double Bullet::getEllapseTime() const {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	return time;
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

	if (DEBUG_ENABLE_BULLET_PATH) {
		glBegin(GL_POINTS);
		for (size_t i = 0; i < this->bulletVector.size(); i++) {
			glVertex2d(this->bulletVector[i].x, this->bulletVector[i].y);
		}
		glEnd();
	}
}

Bullet::Bullet() :centerX(0.0), centerY(0.0), time(0), theta(0.0), groundLevel(0.0), fired(false), velocity(BULLET_VELOCITY) { }