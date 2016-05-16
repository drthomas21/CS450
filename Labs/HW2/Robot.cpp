#include "Robot.h"
#include "lib.h"

void Robot::setX(GLdouble n) {
	this->x = n;
}
void Robot::setY(GLdouble n) {
	this->y = n;
}
void Robot::setZ(GLdouble n) {
	this->z = n;
}
void Robot::setRotate(GLdouble n) {
	this->rotate = n;
}
void Robot::setUpperArmLength(GLdouble n) {
	this->lengthUpperArm = n;
}
void Robot::setLowerArmLength(GLdouble n) {
	this->lengthLowerArm = n;
}
void Robot::setFingerSegmentLength(GLdouble n) {
	this->lengthFingerSegment = n;
}
void Robot::setShoulderAngle(double n) {
	this->angleShoulder = n;
}
void Robot::setArmAngle(double n) {
	this->angleArm = n;
}
void Robot::setHandAngle(double n) {
	this->angleHand = n;
}
void Robot::setFingerAngle(double n) {
	this->angleFinger = n;
}
void Robot::setNumberOfFingers(unsigned int n) {
	this->numOfFingers = n;
}

GLdouble Robot::getX() const {
	return this->x;
}
GLdouble Robot::getY() const {
	return this->y;
}
GLdouble Robot::getZ() const {
	return this->z;
}
GLdouble Robot::getRotate() const {
	return this->rotate;
}
GLdouble Robot::getUpperArmLength() const {
	return this->lengthUpperArm;
}
GLdouble Robot::getLowerArmLength() const {
	return this->lengthLowerArm;
}
GLdouble Robot::getFingerSegmentLength() const {
	return this->lengthFingerSegment;
}
double Robot::getShoulderAngle() const {
	return this->angleShoulder;
}
double Robot::getArmAngle() const {
	return this->angleArm;
}
double Robot::getHandAngle() const {
	return this->angleHand;
}
double Robot::getFingerAngle() const {
	return this->angleFinger;
}
unsigned int Robot::getNumberOfFingers() const {
	return this->numOfFingers;
}

void Robot::draw() {
	//Draw Base
	glBegin(GL_POLYGON);
	for (float t = 0.0; t < 1.0; t += 1.0 / 20) {

	}
	glEnd();

	//Draw shoulder joint

	//Draw lower arm

	//Draw elbow

	//Draw upper arm

	//Draw wrist

	//Draw hand
	
	//Draw fingers
}
void Robot::animate() {

}

Robot::Robot():x(0),y(0),z(0),angleShoulder(PI/2.0),angleArm(PI/2.0),angleHand(PI/2.0),angleFinger(0),lengthFingerSegment(2.5),lengthLowerArm(12.0),lengthUpperArm(9.0),rotate(0), numOfFingers(3) { }