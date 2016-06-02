#include "Robot.h"
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

GLdouble _theta1, _theta2, acceleration, t1, t2, baseRadius = 15.0, thetas[10], timings[10];
unsigned int attackPattern;

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
void Robot::setLowerArmLength(GLdouble n) {
	this->lengthLowerArm = n;
}
void Robot::setUpperArmLength(GLdouble n) {
	this->lengthUpperArm = n;
}
void Robot::setFingerSegmentLength(GLdouble n) {
	this->lengthFingerSegment = n;
}
void Robot::setShoulderAngle(double n) {
	if (!this->isActived) return;
	this->angleShoulder += n;
	if (this->angleShoulder < -max_angle) {
		this->angleShoulder = -max_angle;
	} else if (this->angleShoulder > max_angle) {
		this->angleShoulder = max_angle;
	}
	std::cout << "Shoulder: " << this->angleShoulder << std::endl;
}
void Robot::setArmAngle(double n) {
	if (!this->isActived) return;
	this->angleArm += n;
	if (this->angleArm < -max_angle_elbow) {
		this->angleArm = -max_angle_elbow;
	} else if (this->angleArm > max_angle_elbow) {
		this->angleArm = max_angle_elbow;
	}
	std::cout << "Elbow: " << this->angleArm << std::endl;
}
void Robot::setHandAngle(double n) {
	if (!this->isActived) return;
	this->angleHand += n;
	if (this->angleHand < -max_angle_hand) {
		this->angleHand = -max_angle_hand;
	} else if (this->angleHand > max_angle_hand) {
		this->angleHand = max_angle_hand;
	}
	std::cout << "Hand: " << this->angleHand << std::endl;
}
void Robot::setFingerAngle(double n) {
	if (!this->isActived) return;
	this->angleFinger += n;
	if (this->angleFinger < -max_angle_finger) {
		this->angleFinger = -max_angle_finger;
	} else if (this->angleFinger > 0) {
		this->angleFinger = 0;
	}
	std::cout << "Finger: " << this->angleFinger << std::endl;
}
void Robot::setNumberOfFingers(unsigned int n) {
	this->numOfFingers = n;
}

void Robot::doAttack(unsigned int n, unsigned long time) {
	if (this->isAnimating) return;
	this->time = time;
	switch (n) {
		case 1:
			thetas[0] = 90;
			thetas[1] = 0;

			timings[0] = 0.2;
			timings[1] = 0.5;
			timings[2] = 0.7;

			attackPattern = n;
			this->isAnimating = true;
			break;
		case 2:
			thetas[0] = 90;
			thetas[1] = 45;
			thetas[2] = -45;
			thetas[3] = 90;

			timings[0] = 0.2;
			timings[1] = 0.6;
			timings[2] = 0.8;
			attackPattern = n;
			this->isAnimating = true;
		case 3:
			attackPattern = n;
			this->isAnimating = true;
			break;
	}
}

void Robot::toggleActivation() {
	this->isActived = !this->isActived;
}

void Robot::toggleWireframe() {
	this->isWireframe = !this->isWireframe;
}

void Robot::toggleAnimation() {
	if (this->isAnimating) {
		this->stopAnimation();
	} else {
		this->startAnimation();
	}
}

void Robot::startAnimation() {
	this->isAnimating = true;

	this->angleFinger = -max_angle_finger;
	if (this->angleArm == 0 && this->angleShoulder == 0) {
		this->angleHand = 0;
	}
	else if (this->angleArm <= 0 && this->angleShoulder <= 0) {
		this->angleHand = max_angle_hand;
	}
	else if (this->angleArm >= 0 && this->angleShoulder >= 0) {
		this->angleHand = -max_angle_hand;
	}
	else if (abs(this->angleArm) < abs(this->angleShoulder)) {
		this->angleHand = max_angle_hand;
	}
	else if (abs(this->angleArm) > (this->angleShoulder)) {
		this->angleHand = -max_angle_hand;
	}

	_theta1 = this->angleArm;
	_theta2 = this->angleShoulder;

	acceleration = robot_force;

	t1 =
		pow(abs((
		(2.0 * pi * this->lengthLowerArm * 0.25)
			- (2.0 * pi * this->lengthLowerArm * (90.0 + this->angleArm) / 360.0))
			/ acceleration), 0.5);
	t2 =
		pow(abs((
		(2.0 * pi * this->lengthUpperArm * 0.25)
			- (2.0 * pi * this->lengthUpperArm * (90.0 + this->angleShoulder) / 360.0))
			/ acceleration), 0.5);
}

void Robot::stopAnimation() {
	this->isAnimating = false;
}

void Robot::reset() {
	this->angleArm = 0;
	this->angleFinger = 0;
	this->angleHand = 0;
	this->angleShoulder = 0;
	this->rotate = 0;

	this->isActived = false;
	this->isAnimating = false;
	this->isWireframe = false;
}

void Robot::applySkinMaterial() {
	GLfloat mat[4], ambr, ambg, ambb, difr, difg, difb, specr, specg, specb, shine;
	ambr = 0.25, ambg = 0.25, ambb = 0.25;
	difr = 0.4, difg = 0.4, difb = 0.4;
	specr = 0.574597, specg = 0.574597, specb = 0.574597;
	shine = 0.6;
	mat[0] = ambr;
	mat[1] = ambg;
	mat[2] = ambb;
	mat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	mat[0] = difr;
	mat[1] = difg;
	mat[2] = difb;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = specr;
	mat[1] = specg;
	mat[2] = specb;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
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
GLdouble Robot::getBaseRadius() const {
	return baseRadius;
}
GLdouble Robot::getRotate() const {
	return this->rotate;
}
GLdouble Robot::getLowerArmLength() const {
	return this->lengthLowerArm;
}
GLdouble Robot::getUpperArmLength() const {
	return this->lengthUpperArm;
}
GLdouble Robot::getFingerSegmentLength() const {
	return this->lengthFingerSegment;
}
GLdouble Robot::getShoulderAngle() const {
	return this->angleShoulder;
}
GLdouble Robot::getArmAngle() const {
	return this->angleArm;
}
GLdouble Robot::getHandAngle() const {
	return this->angleHand;
}
GLdouble Robot::getFingerAngle() const {
	return this->angleFinger;
}
unsigned int Robot::getNumberOfFingers() const {
	return this->numOfFingers;
}

void Robot::draw() {
	glPushMatrix();
		glTranslated(this->x, this->y, this->z);

		//Draw Base
		this->applySkinMaterial();
		glPushMatrix();
			glTranslated(0, 0, 0);
			glScaled(1.0, 0.1, 1.0);
			if (this->isWireframe) {
				glutWireSphere(baseRadius, 20, 20);
			} else {
				glutSolidSphere(baseRadius, 20, 20);
			}
		glPopMatrix();

		glPushMatrix();
			glRotated(this->rotate, 0, 1, 0);

			//Draw shoulder joint
			glPushMatrix();
				glTranslated(0, 3.0, 0);
				if (this->isWireframe) {
					glutWireSphere(4.0, 20, 20);
				} else {
					glutSolidSphere(4.0, 20, 20);
				}

				//Draw upper arm
				glRotated(this->angleShoulder, 0, 0, 1);
				GLdouble shifted = this->lengthUpperArm / 2.0;
				glPushMatrix();
					glTranslated(0, shifted, 1.25);
					glScaled(1.25, shifted, 0.5);
					if (this->isWireframe) {
						glutWireCube(2);
					} else {
						glutSolidCube(2);
					}
				glPopMatrix();

				glPushMatrix();
					glTranslated(0, shifted, -1.25);
					glScaled(1.25, shifted, 0.5);
					if (this->isWireframe) {
						glutWireCube(2);
					}
					else {
						glutSolidCube(2);
					}
				glPopMatrix();

				//Draw elbow
				glPushMatrix();
					glTranslated(0, this->lengthUpperArm, 0);
					if (this->isWireframe) {
						glutWireSphere(2.5, 10, 10);
					} else {
						glutSolidSphere(2.5, 10, 10);
					}

					//Draw upper arm
					glRotated(this->angleArm, 0, 0, 1);
					shifted = this->lengthLowerArm / 2.0;
					glPushMatrix();
						glTranslated(0, shifted, 0);
						glScaled(1.25, shifted, 0.5);
						if (this->isWireframe) {
							glutWireCube(2);
						} else {
							glutSolidCube(2);
						}
					glPopMatrix();

					//Draw wrist
					glPushMatrix();
						glTranslated(0, this->lengthLowerArm, 0);
						glRotated(this->angleHand, 0, 0, 1);

						//Draw hand
						if (this->isWireframe) {
							glutWireSphere(1.75, 10, 10);
						}
						else {
							glutSolidSphere(1.75, 10, 10);
						}

						glPushMatrix();
							glTranslated(1.9, 0, 0);
							glutSolidSphere(0.5, 5, 5);
						glPopMatrix();

						glPushMatrix();
							glTranslated(-1.9, 0, 0);
							glutSolidSphere(0.5, 5, 5);
						glPopMatrix();

						glPushMatrix();
							glTranslated(0, 0, 1.9);
							glutSolidSphere(0.5, 5, 5);
						glPopMatrix();

						glPushMatrix();
							glTranslated(0, 0, -1.9);
							glutSolidSphere(0.5, 5, 5);
						glPopMatrix();
	
						//Draw fingers
						GLdouble fingerRotation = 360.0 / this->numOfFingers;
						shifted = this->lengthLowerArm / 2.0;
						GLdouble radius = 0.85;
					
						for (unsigned int f = 0; f < this->numOfFingers; f++) {
							glPushMatrix();
								glRotated(fingerRotation * (double)f, 0, 1, 0);
								glTranslated(radius, 0, 0);
								glRotated(this->angleFinger, 0, 0, 1);

								//Upper finger segement
								glPushMatrix();	
									glTranslated(0, shifted / 2.0, 0);
									glScaled(1, shifted, 1);

									if (this->isWireframe) {
										glutWireCube(0.5);
									}
									else {
										glutSolidCube(0.5);
									}
								glPopMatrix();

								glTranslated(0, 3.0*shifted / 4.0, 0);

								//Draw fingerSegment joint
								glPushMatrix();								
									if (this->isWireframe) {
										glutWireSphere(0.5, 5, 5);
									}
									else {
										glutSolidSphere(0.5, 5, 5);
									}
								glPopMatrix();

								//Draw lower finger segment
								glPushMatrix();
									glTranslated(0.75 * this->angleFinger / 30.0, shifted / 4.0, 0);
									glRotated(-this->angleFinger, 0, 0, 1);
									glScaled(1, shifted, 1);								
									if (this->isWireframe) {
										glutWireCube(0.5);
									}
									else {
										glutSolidCube(0.5);
									}
								glPopMatrix();
							glPopMatrix();
						}
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
void Robot::animate(unsigned long time) {
	if (!this->isAnimating) return;
	time -= this->time;

	GLdouble _time = static_cast<double>(time) / 1000.0;
	std::cout << _time << " " << timings[0] << std::endl;
	if (attackPattern == 1) {
		if (_time <= timings[0]) {
			this->angleShoulder = thetas[0] * _time / timings[0];
		} else if(_time >= timings[1] && _time < timings[2]) {
			this->angleShoulder = thetas[0] * (timings[2] - _time) / timings[2];
		} else if(_time > timings[2]) {
			this->angleShoulder = 0;
			this->isAnimating = false;
		}
	} else if (attackPattern == 2) {
		if (_time <= timings[0]) {
			this->rotate = thetas[1];
			this->angleShoulder = thetas[0] * _time / timings[0];
		} else if (_time <= timings[1]) {
			this->angleHand = thetas[3];
			this->rotate = thetas[0];
			this->angleShoulder = thetas[1] * _time / timings[0];
		} else if (_time <= timings[2]) {
			this->angleHand = thetas[3];
			this->rotate = thetas[0];
			this->angleShoulder = thetas[1] * _time / timings[0];
		} else {
			this->rotate = 0;
			this->angleShoulder = 0;
			this->angleHand = 0;
			this->isAnimating = false;
		}
	} else if (attackPattern == 3) {
		this->isAnimating = false;
	}
}

Robot::Robot():x(0),y(0),z(0),angleShoulder(0),angleArm(0),angleHand(0),angleFinger(0),lengthFingerSegment(3.0),lengthUpperArm(12.0),lengthLowerArm(9.0),rotate(0), numOfFingers(5), isActived(true) { 

}