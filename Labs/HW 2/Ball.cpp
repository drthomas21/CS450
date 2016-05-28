#include "Ball.h"
#include "lib.h"
#include <math.h>
#include <iostream>

GLdouble _force = 0, _x = 0, _y = 0, _z = 0;
void Ball::setX(GLdouble n) {
	this->x = n;
}
void Ball::setY(GLdouble n) {
	this->y = n;
}
void Ball::setZ(GLdouble n) {
	this->z = n;
}
void Ball::setRadius(GLdouble n) {
	this->radius = n;
}
void Ball::setRotated(GLdouble n) {
	this->rotated = n;
}
void Ball::setTheta(GLdouble n) {
	this->theta = n;
}
void Ball::setVelocity(GLdouble n) {
	this->velocity = n;
}
void Ball::setBoundryHeight(GLdouble n) {
	this->boundryHeight = n;
}
void Ball::setBoundryWidth(GLdouble n) {
	this->boundryWidth = n;
}

void Ball::startAnimation() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	this->isAnimating = true;
	this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	_force = this->velocity * ball_mass;
	std::cout << "Force = " << _force << " | velocity = " << this->velocity << " | theta = " << this->theta << " | rotated = " << this->rotated << std::endl;
	_x = this->x * cos(this->rotated);
	this->x = _x;
	_y = this->y;
	this->y = _y;
	_z = this->z * -sin(this->rotated);
	this->z = _z;
}
void Ball::stopAnimation() {
	this->isAnimating = false;
}

void Ball::showBall() {
	this->isShown = true;
}

void Ball::hideBall() {
	this->isShown = false;
}

void Ball::reset() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->isAnimating = false;
	this->isShown = false;
}

GLdouble Ball::getX() {
	return this->x;
}
GLdouble Ball::getY() {
	return this->y;
}
GLdouble Ball::getZ() {
	return this->z;
}
GLdouble Ball::getRadius() {
	return this->radius;
}
GLdouble Ball::getRotated() {
	return this->rotated;
}
GLdouble Ball::getTheta() {
	return this->theta;
}
GLdouble Ball::getVelocity() {
	return this->velocity;
}

GLdouble Ball::getForce() {
	return ball_mass * gravity;
}

GLdouble Ball::getMass() {
	return ball_mass;
}

void Ball::animate() {
	if (!this->isAnimating || !this->isShown) return;

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	//_force -= _force * AIR_FRICTION;
	GLdouble forceVertical = sin(this->theta) * _force - this->getForce();
	GLdouble forceHorizontal = cos(this->theta) * _force;
	GLdouble __x = this->x, __y = this->y, __z = this->z;
	
	this->x = _x + (this->velocity * cos(this->theta) * time) * cos(this->rotated);
	this->y = _y + this->velocity * sin(this->theta) * time + 0.5 * (forceVertical / ball_mass) * pow(time, 2.0);
	this->z = _z + (this->velocity * cos(this->theta) * time) * -sin(this->rotated);

	GLdouble dx = pow(this->x * this->x + this->z * this->z, 0.5);
	GLdouble __dx = pow(__x * __x + __z * __z, 0.5);
	if (this->y < 0 || this->y > this->boundryHeight) {
		if (dx != 0 || __dx != 0) {
			GLdouble x = dx - __dx, y = this->y - __y;
			GLdouble theta = atan(dx / y);
			//std::cout << "ytheta = " << theta << " | x = " << dx << ", y = " << y << std::endl;
			this->theta = theta;
		} else {
			//std::cout << "ytheta = " << pi << " | x = " << dx << ", y = " << y << std::endl;
			this->theta += pi;
		}
		
		this->y = this->y < 0 ? 0 : this->boundryHeight;

		_x = this->x;
		_z = this->z;
		_y = this->y;
		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	} 

	if (this->x < -this->boundryWidth || this->x > this->boundryWidth) {
		if (this->z != 0 || __z != 0) {
			GLdouble x = this->x - __x, z = this->z - __z;
			GLdouble theta = atan(z / x);
			//std::cout << "xtheta = " << theta << " | x = " << x << ", z = " << z << std::endl;
			this->rotated = theta;
		} else {
			//std::cout << "xtheta = " << pi << " | x = " << x << ", z = " << z << std::endl;
			this->rotated += pi;
		}
		this->x = this->x < -this->boundryWidth ? -this->boundryWidth : this->boundryWidth;

		_x = this->x;
		_z = this->z;
		_y = this->y;
		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}

	if (this->z < -this->boundryWidth || this->z > this->boundryWidth) {
		if(this->x != 0 || __x != 0) {
			GLdouble x = this->x - __x, z = this->z - __z;
			GLdouble theta = atan(x / z);
			//std::cout << "ztheta = " << theta << " | x = " << x << ", z = " << z << std::endl;
			this->rotated = theta;
		} else {
			//std::cout << "ztheta = " << pi << " | x = " << x << ", z = " << z << std::endl;
			this->rotated += pi;
		}
		
		this->z = this->z < -this->boundryWidth ? -this->boundryWidth : this->boundryWidth;

		_x = this->x;
		_z = this->z;
		_y = this->y;
		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}

	
}
void Ball::draw(bool isWireframe) {
	if (!this->isShown) return;

	glPushMatrix();
		glColor3d(0.8, 0.1, 0.1);
		//glRotated(rotate, 0, 1, 0);
		glTranslated(this->x,this->y,this->z);
		if (isWireframe) {
			glutWireSphere(this->radius, 20, 20);
		} else {
			glutSolidSphere(this->radius, 20, 20);
		}
	glPopMatrix();
}

Ball::Ball() :radius(1.0), x(0), y(0), z(0), isAnimating(false), isShown(false) {}