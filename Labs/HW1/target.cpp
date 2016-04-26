#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include "target.h"
#include "lib.h"

void Target::setX(double x) {
	this->centerX = x;
	this->_centerX = x;
}

void Target::setY(double y) {
	this->centerY = y;
	this->_centerY = y;
}

void Target::setVelocity(double v) {	
	if (this->velocityX > 0 && this->velocityY > 0) {
		this->theta = atan(this->velocityX / this->velocityY);
	} else if ((this->velocityX < 0 && this->velocityY > 0) || (this->velocityX < 0 && this->velocityY < 0)) {
		this->theta = atan(this->velocityX / this->velocityY) + PI;
	} else if (this->velocityX > 0 && this->velocityY < 0) {
		this->theta = atan(this->velocityX / this->velocityY) + 2.0 * PI;
	} else if (this->velocityX == 0) {		this->theta = PI / 4.0 + (this->velocityY > 0 ? 0 : PI);	} else if (this->velocityY == 0) {		this->theta = 0 + (this->velocityX > 0 ? 0 : PI);	}

	this->velocityX = v * cos(this->theta);
	this->velocityY = v * sin(this->theta);
}

void Target::flipVelocityX() {
	this->velocityX *= -1;
}

void Target::flipVelocityY() {
	this->velocityY *= -1;
}

void Target::toggleMovement() {
	this->moving = !this->moving;
	if (this->moving) {
		this->velocityX = TARGET_VELOCITY * cos(this->theta);
		this->velocityY = TARGET_VELOCITY * cos(this->theta);
		
		this->theta = ((double)(rand() % (360))) * (PI / 180.0);
		if (DEBUG_ENABLE_TARGET) std::cout << "Theta: " << this->theta << std::endl;
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
		this->_time = this->time;
	} else {
		this->velocityX = 0;
		this->velocityY = 0;
		this->theta = 0;
	}
}

void Target::checkCollision(Bullet &bullet) {
	double x = this->centerX - bullet.getX();
	double y = this->centerY - bullet.getY();
	double d = pow((x * x) + (y * y),0.5) - this->RADIUS - bullet.RADIUS;
	if (d <= 4.0) {
		if(DEBUG_ENABLE_TARGET) std::cout << "collision" << std::endl;

		double time = bullet.getEllapseTime();
		double bulletVelocityX = BULLET_VELOCITY * cos(bullet.getTheta());
		double bulletVelocityY = BULLET_VELOCITY * sin(bullet.getTheta()) - GRAVITY * time;
		std::cout << "Time: " << time << std::endl;

		double rVelocityX = bulletVelocityX - this->velocityX;
		double rVelocityY = bulletVelocityY - this->velocityY;

		this->theta = atan(rVelocityX / rVelocityY);
		this->velocityX = rVelocityX;
		this->velocityY = rVelocityY;
		
		if(DEBUG_ENABLE_TARGET) std::cout << "Velocity: " << this->getVelocity() << " | Theta: " << this->theta << std::endl;
		if (DEBUG_ENABLE_TARGET) std::cout << "Velocity X: " << this->velocityX << " | Velocity Y: " << this->velocityY << std::endl;

		if (!this->moving) {
			FILETIME ft;
			GetSystemTimeAsFileTime(&ft);
			this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
			this->moving = true;
		}

		bullet.hitTarget();
	}
}

void Target::calculatePosition() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double incr = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	this->centerX += this->velocityX * incr;
	this->centerY += this->velocityY * incr;

	time += diff;
}

double Target::getX() const {
	return this->centerX;
}

double Target::getY() const {
	return this->centerY;
}

double Target::getVelocity() const {
	return pow((this->velocityX * this->velocityX) + (this->velocityY * this->velocityY) , 0.5);
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

Target::Target() :centerX(0.0), centerY(0.0), xFactor(1.0), yFactor(1.0), moving(false) {
	this->toggleMovement();
	this->velocityX = TARGET_VELOCITY * cos(this->theta);
	this->velocityY = TARGET_VELOCITY * sin(this->theta);
}
