#include "SpaceObject.h"
#include <math.h>

#define PI 3.1415

void SpaceObject::setX(GLdouble n) {
	this->x = n;
}
void SpaceObject::setY(GLdouble n) {
	this->y = n;
}
void SpaceObject::setZ(GLdouble n) {
	this->z = n;
}
void SpaceObject::setParent(SpaceObject *_parent) {
	if (this->parent != nullptr) {
		delete this->parent;
	}
	
	this->parent = _parent;
}
void SpaceObject::setRotate(GLdouble n) {
	this->rotateSpeed = n;
}
void SpaceObject::setRotateVectorX(GLdouble n) {
	this->rotateVectorX = n;
}
void SpaceObject::setRotateVectorY(GLdouble n) {
	this->rotateVectorY = n;
}
void SpaceObject::setRotateVectorZ(GLdouble n) {
	this->rotateVectorZ = n;
}
void SpaceObject::setOrbitRadiusX(GLdouble n) {
	this->orbitRadiusX = n;
}
void SpaceObject::setOrbitRadiusY(GLdouble n) {
	this->orbitRadiusY = n;
}
void SpaceObject::setOrbitRadiusZ(GLdouble n) {
	this->orbitRadiusZ = n;
}
void SpaceObject::setOrbitSpeed(GLdouble n) {
	this->orbitSpeed = n;
}
void SpaceObject::setScale(GLdouble n) {
	this->scale = n;
}
void SpaceObject::setRadius(GLdouble n) {
	this->radius = n;
}
void SpaceObject::setSlices(GLint n) {
	this->slices = n;
}
void SpaceObject::setStacks(GLint n) {
	this->stacks = n;
}
GLdouble SpaceObject::getX() {
	if (this->parent == nullptr) {
		return this->x;
	} else {
		return this->x + this->parent->getX();
	}	
}
GLdouble SpaceObject::getY() {
	if (this->parent == nullptr) {
		return this->y;
	}
	else {
		return this->y + this->parent->getY();
	}
}
GLdouble SpaceObject::getZ() {
	if (this->parent == nullptr) {
		return this->z;
	}
	else {
		return this->z + this->parent->getZ();
	}
}
GLdouble SpaceObject::getRotate() {
	return this->rotateSpeed;
}
GLdouble SpaceObject::getRotateVectorX() {
	return this->rotateVectorX;
}
GLdouble SpaceObject::getRotateVectorY() {
	return this->rotateVectorY;
}
GLdouble SpaceObject::getRotateVectorZ() {
	return this->rotateVectorZ;
}
GLdouble SpaceObject::getOrbitRadiusX() {
	return this->orbitRadiusX;
}
GLdouble SpaceObject::getOrbitRadiusY() {
	return this->orbitRadiusY;
}
GLdouble SpaceObject::getOrbitRadiusZ() {
	return this->orbitRadiusZ;
}
GLdouble SpaceObject::getOrbitSpeed() {
	return this->orbitSpeed;
}
GLdouble SpaceObject::getScale() {
	return this->scale;
}
GLdouble SpaceObject::getRadius() {
	return this->radius;
}
GLint SpaceObject::getSlices() {
	return this->slices;
}
GLint SpaceObject::getStacks() {
	return this->stacks;
}
void SpaceObject::animate() {
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);

	long long diff = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL) - this->time; //nanoseconds
	double time = static_cast<double>(static_cast<long double>(diff) / static_cast<long double>(10000000.0)); //seconds

	if (this->isAnimating) {
		this->x = this->orbitRadiusX * cos(2.0 * PI * time * this->orbitSpeed);
		this->y = this->orbitRadiusY * sin(2.0 * PI * time * this->orbitSpeed);
		this->z = this->orbitRadiusZ * cos(2.0 * PI * time * this->orbitSpeed);
		//this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}
	this->rotate = time * this->rotateSpeed;
}
void SpaceObject::toggleOrbit() {
	this->isAnimating = !this->isAnimating;

	if (this->isAnimating) {
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}
}
void SpaceObject::draw() {
	glPushMatrix();
	if (this->parent == nullptr) {		
		glTranslated(this->x, this->y, this->z);
	} else {		
		glTranslated(this->x + this->parent->getX(), this->y + this->parent->getY(), this->z + this->parent->getZ());
	}
	glScaled(this->scale, this->scale, this->scale);
	glRotated(this->rotate, this->rotateVectorX, this->rotateVectorY, this->rotateVectorZ);
	glutSolidSphere(this->radius, this->slices, this->stacks);
	//glutWireSphere(this->radius, this->slices, this->stacks);
	glPopMatrix();

	if (this->isAnimating && this->parent != nullptr) {
		glBegin(GL_LINE_LOOP);
		for (double i = 0; i < 1; i += 0.02) {
			GLdouble x = this->orbitRadiusX * cos(2.0 * PI * i);
			GLdouble y = this->orbitRadiusY * sin(2.0 * PI * i);
			GLdouble z = this->orbitRadiusZ * cos(2.0 * PI * i);
			glVertex3d(x + this->parent->getX(), y + this->parent->getY(), z + this->parent->getZ());
		}
		glEnd();
	}		
}

void SpaceObject::operator=(SpaceObject &source) {
	this->x = source.x;
	this->y = source.y;
	this->z = source.z;
	this->rotate = source.rotate;
	this->rotateVectorX = source.rotateVectorX;
	this->rotateVectorY = source.rotateVectorY;
	this->rotateVectorZ = source.rotateVectorZ;
	this->orbitRadiusX = source.orbitRadiusX;
	this->orbitRadiusY = source.orbitRadiusY;
	this->orbitRadiusZ = source.orbitRadiusZ;
	this->orbitSpeed = source.orbitSpeed;
	this->scale = source.scale;
	this->radius = source.radius;
	this->slices = source.slices;
	this->stacks = source.stacks;
	this->parent = source.parent;
	this->isAnimating = source.isAnimating;
}

SpaceObject::SpaceObject(): parent(nullptr), x(0), y(0), z(0), rotate(0), rotateVectorX(0), rotateVectorY(0), rotateVectorZ(0), orbitRadiusX(1), orbitRadiusY(1), orbitRadiusZ(1), orbitSpeed(1),scale(1), radius(1), slices(10), stacks(10), isAnimating(true) { 
	if (this->isAnimating) {
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);

		this->time = static_cast<long long>(ft.dwLowDateTime) + (static_cast<long long>(ft.dwHighDateTime) << 32LL);
	}
}
SpaceObject::~SpaceObject() {
	
}