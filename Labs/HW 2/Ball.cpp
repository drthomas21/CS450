#include "Ball.h"
#include <math.h>

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
void Ball::setTheta(GLdouble n) {
	this->theta = n;
}
void Ball::setVelocity(GLdouble n) {
	this->velocity = n;
}

void Ball::startAnimation() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	this->isAnimating = true;
	this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	_force = this->velocity * BALL_MASS;
	_x = this->x;
	_y = this->y;
	_z = this->z;
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
GLdouble Ball::getTheta() {
	return this->theta;
}
GLdouble Ball::getVelocity() {
	return this->velocity;
}

GLdouble Ball::getForce() {
	return BALL_MASS * GRAVITY;
}

GLdouble Ball::getMass() {
	return BALL_MASS;
}

void Ball::animate() {
	if (!this->isAnimating || !this->isShown) return;

	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	//_force -= _force * AIR_FRICTION;
	GLdouble forceVertical = sin(this->theta) * _force - BALL_MASS * GRAVITY;
	GLdouble forceHorizontal = cos(this->theta) * _force;
	
	this->x = _x + this->velocity * cos(this->theta) * time;
	this->y = _y + this->velocity * sin(this->theta) * time + 0.5 * (GRAVITY) * pow(time,2.0);
	this->z = _z + 0;
}
void Ball::draw(bool isWireframe, GLdouble rotate) {
	if (!this->isShown) return;

	glPushMatrix();
		glColor3d(0.8, 0.1, 0.1);
		glRotated(rotate, 0, 1, 0);
		glTranslated(this->x,this->y,this->z);
		if (isWireframe) {
			glutWireSphere(this->radius, 20, 20);
		} else {
			glutSolidSphere(this->radius, 20, 20);
		}
	glPopMatrix();
}

Ball::Ball() :radius(1.0), x(0), y(0), z(0), isAnimating(false), isShown(false) {}